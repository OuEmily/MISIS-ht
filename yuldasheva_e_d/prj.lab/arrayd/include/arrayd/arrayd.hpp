#pragma once

#ifndef ARRAYDHPP
#define ARRAYDHPP

#include <cstddef>
#include <iostream>



class ArrayD {
public:
	ArrayD() = default;
	
	// {
	// 	start_ = new double[capacity_]; {0.0;}
	// }
	ArrayD(const std::ptrdiff_t n); // контруктор создает массив заданного размера n
	ArrayD(const ArrayD& rhs); // конструктор копирования
	//Arrayd(const std::ptrdiff_t& size, const doubl& fill);

	double& operator[](std::ptrdiff_t i); // для присваивания
	const double& operator[](const std::ptrdiff_t i) const; // для чтения
	ArrayD& operator=(const ArrayD& arr);
	//ArrayD& operator=(const ArrayD& arr) = default;


	void resize(const std::ptrdiff_t new_size);
	void push_back(const double& el);
	void insert(std::ptrdiff_t index, const double& el); // вствить в необходимое место
	void remove(const std::ptrdiff_t ind); // удаление элемента с текущим индексом
	std::ptrdiff_t ssize() const noexcept;
// const после функции говорит что в функции ничего не изменяется
	~ArrayD() = default;

private:
	std::ptrdiff_t array_size_ = { 0 };//фактический размер
	std::ptrdiff_t capacity_ = { 0 };// логический размер (незаполненная часть массива)
	double* start_ = { nullptr }; // отсылает на невалидный адресс (непосредственно наш массив)
};
/* ArrayD(std::initializer_list<double> rhs) {
		double* new_start = new double[rhs.size()];
		if (new_start != nullptr) {
			for (int i = 0; i < rhs.size(); i += 1) {
				new_start[i] = *(rhs.begin() + i);
			}
			array_size_ = rhs.size();
			capacity_ = array_size_ + 10;
			start_ = new_start;
		}
	} */

#endif 