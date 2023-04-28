#include "include/arrayt/arrayt.hpp"
#include <iostream>

/* 
ArrayD::ArrayD(const std::ptrdiff_t n) {
		
        if (n < 0) {
			throw std::invalid_argument("invalid argumet");
		}
		array_size_ = n;
		start_ = new double[n]; {0.0;};
		capacity_ = n *2;
	}

ArrayD::ArrayD(const ArrayD& rhs) {
    
    start_ = new double[rhs.ssize()];
    capacity_ = rhs.capacity_;
    array_size_ = rhs.ssize();
    for(std::ptrdiff_t i = 0; i < rhs.ssize(); i++) {
        start_[i] = rhs[i];
    }

}

double& ArrayD::operator[](std::ptrdiff_t i)
{
    if (i < 0 || i >= array_size_) {
		throw std::out_of_range("Out of range");
	}
	return *(start_ + i);
}

const double& ArrayD::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= array_size_) {
		throw std::out_of_range("Out of range");
    }
	return *(start_ + i);
}


ArrayD& ArrayD::operator=(const ArrayD& arr) {
	if (&arr != this) {
        array_size_ = arr.ssize();
        capacity_ =  arr.capacity_; // логический размеp
        delete[] start_;
        start_ = new double[arr.ssize()];
        for (std::ptrdiff_t i = 0; i < arr.ssize(); i++) {
            start_[i] = arr[i];
        }
	}
	return *this;
}


void ArrayD::resize(const std::ptrdiff_t new_size) {
		if (new_size <= 0) {
			throw std::out_of_range("Out of range");
		}
		else if (new_size <= capacity_) {
			array_size_ = new_size;
			return;
		}
        else {
            double* new_start = new double[new_size*2]; {0.0;}
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
void ArrayD::push_back(const double& el) { // вставляем элемент в конец
	resize(ssize() + 1);
	start_[ssize() - 1] = el;
}

void ArrayD::insert(std::ptrdiff_t index, const double& el) {
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
void ArrayD::remove(const std::ptrdiff_t ind) {
	for (int i = ind; i < array_size_ - 1; i += 1) {
		std::swap(start_[i], start_[i + 1]);
	}
    array_size_ -= 1;
}

std::ptrdiff_t ArrayD::ssize() const noexcept{
		return array_size_;
	}
*/
