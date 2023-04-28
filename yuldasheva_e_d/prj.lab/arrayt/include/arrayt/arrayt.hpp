#pragma once

#ifndef ARRAYTHPP
#define ARRAYTHPP

#include <iostream>
#include <cstddef>


//const std::exception out_of_range("Error: Out of range");

template <typename T>

class ArrayT {
public:
	ArrayT() = default;
	
	// {
	// 	start_ = new double[capacity_]; {0.0;}
	// }
	ArrayT(const std::ptrdiff_t n); // контруктор создает массив заданного размера n
	ArrayT(const ArrayT& rhs); // конструктор копирования
	//ArrayD(const std::ptrdiff_t& size, const doubl& fill);

	T& operator[](std::ptrdiff_t i); // для присваивания
	const T& operator[](const std::ptrdiff_t i) const; // для чтения
	ArrayT& operator=(const ArrayT& arr);
	//ArrayD& operator=(const ArrayD& arr) = default;


	void resize(const std::ptrdiff_t new_size);
	void push_back(const T& el);
	void insert(std::ptrdiff_t index, const T& el); // вствить в необходимое место
	void remove(const std::ptrdiff_t ind); // удаление элемента с текущим индексом
	std::ptrdiff_t ssize() const noexcept;
// const после функции говорит что в функции ничего не изменяется
	~ArrayT() = default;

private:
	std::ptrdiff_t array_size_ = { 0 };//фактический размер
	std::ptrdiff_t capacity_ = { 0 };// логический размер (незаполненная часть массива)
	T* start_ = { nullptr }; // отсылает на невалидный адресс (непосредственно наш массив)
};

template<typename T>

ArrayT<T>::ArrayT(const std::ptrdiff_t n) {
		
        if (n < 0) {
			throw std::invalid_argument("invalid argumet");
		}
		array_size_ = n;
		start_ = new T[n*2]; {T();};
		capacity_ = n *2;
	}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& rhs) {
    
    start_ = new T[rhs.ssize()];
    capacity_ = rhs.capacity_;
    array_size_ = rhs.ssize();
    for(std::ptrdiff_t i = 0; i < rhs.ssize(); i++) {
        start_[i] = rhs[i];
    }

}

template<typename T>
T& ArrayT<T>::operator[](std::ptrdiff_t i)
{
    if (i < 0 || i >= array_size_) {
		throw std::out_of_range("Out of range");
	}
	return *(start_ + i);
}

template<typename T>
const T& ArrayT<T>::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= array_size_) {
		throw std::out_of_range("Out of range");
    }
	return *(start_ + i);
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& arr) {
	if (&arr != this) {
        array_size_ = arr.ssize();
        capacity_ =  arr.capacity_; // логический размеp
        delete[] start_;
        start_ = new T[arr.ssize()];
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i++) {
            start_[i] = arr[i];
        }
	}
	return *this;
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
		if (new_size <= 0) {
			throw std::out_of_range("Out of range");
		}
		else if (new_size <= capacity_) {
			array_size_ = new_size;
			return;
		}
        else {
            T* new_start = new T[new_size*2]; {T();}
			for (int t=0; t < new_size * 2; t++) {
				new_start[t] = 0;
			}
            if (new_start != nullptr) {
                for (std::ptrdiff_t i = 0; i < ssize(); i += 1) {
                    new_start[i] = start_[i];
                }
                delete[] start_;
			    start_ = new_start;
			    array_size_ = new_size; // фактический размер
			    capacity_ = new_size * 2;// логический размер с хвостом
            }
        }
		

	}

template<typename T>
void ArrayT<T>::push_back(const T& el) { // вставляем элемент в конец
	resize(ssize() + 1);
	start_[ssize() - 1] = el;
}

template<typename T>
void ArrayT<T>::insert(std::ptrdiff_t index, const T& el) {
    if (index < 0 || index > array_size_){
        throw std::out_of_range("Out of range");
    }
	push_back(el);
	for (int i = ssize() - 1; i >= index + 1; i -= 1) {
		if (i - 1 >= 0) {
			std::swap(start_[i], start_[i - 1]);
		}
		else {
			break;
		}
	}
}

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t ind) {
	for (int i = ind; i < array_size_ - 1; i += 1) {
		std::swap(start_[i], start_[i + 1]);
	}
    array_size_ -= 1;
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept{
		return array_size_;
	}

#endif
