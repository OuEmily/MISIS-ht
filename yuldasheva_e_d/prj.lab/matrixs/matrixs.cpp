#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row < 0 || col < 0) {
        throw std::invalid_argument("Invalid argument");
    }
    n_cols_ = col;
    n_rows_ = row;
    values_ = new int64_t[col * row];
    for (int i = 0; i < row * col; i += 1) {
        values_[i]=0;
    }
}
MatrixS::MatrixS(const MatrixS& other) {
    n_cols_ = other.nCols();
    n_rows_ = other.nRows();
    values_ = new int64_t[n_cols_ * n_rows_];
    for (std::ptrdiff_t k = 0; k < n_cols_ * n_rows_; k += 1) {
        values_[k] = other.values_[k];
    }
}
MatrixS::MatrixS(const SizeType& size) {
    if (std::get<0>(size) < 0 || std::get<1>(size)<0) {
        throw std::out_of_range("Out of range");
    }
    n_cols_ = std::get<1>(size);
    n_rows_ = std::get<0>(size);
    values_ = new int64_t[n_cols_ * n_rows_];
    for (int i = 0; i < n_rows_ * n_cols_; i += 1) {
        values_[i] = 0;
    }
}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    if (this != &other) {
        delete[] values_;
        n_cols_ = other.nCols();
        n_rows_ = other.nRows();
        values_ = new int64_t[n_cols_ * n_rows_];
        for (int i = 0; i < n_cols_; i += 1) {
            for (int j = 0; j < n_rows_; j += 1) {
                values_[i * n_cols_ + j] = other.values_[i * n_rows_ + j];
            }
        }

    }
    return *this;
}




int64_t& MatrixS::at(const SizeType& elem) {
    if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
        throw std::out_of_range("Out of range");
    }
    if (std::get<1>(elem) >= n_cols_ || std::get<0>(elem) >= n_rows_) {
        throw std::out_of_range("Out of range");
    }
    return values_[std::get<0>(elem) * n_cols_ + std::get<1>(elem)];
}
const int64_t& MatrixS::at(const SizeType& elem) const {
    if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
        throw std::out_of_range("Out of range");
    }
    if (std::get<1>(elem) >= n_cols_ || std::get<0>(elem) >= n_rows_) {
        throw std::out_of_range("Out of range");
    }
    return values_[std::get<0>(elem) * n_cols_ + std::get<1>(elem)];
}
int64_t& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i < 0 || j < 0) {
        throw std::out_of_range("Out of range");
    }
    if (j >= n_cols_ || i >= n_rows_) {
        throw std::out_of_range("Out of range");
    }
    return values_[i * n_cols_ + j];
}
const int64_t& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i < 0 || j < 0) {
        throw std::out_of_range("Out of range");
    }
    if (j >= n_cols_ || i >= n_rows_) {
        throw std::out_of_range("Out of range");
    }
    return values_[i * n_cols_ + j];
}

void MatrixS::resize(const SizeType& new_size) {
    this->resize(std::get<0>(new_size), std::get<1>(new_size));
}
void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i <= 0 || j <= 0) {
        throw std::out_of_range("Out of range");
    }
    else {
        int64_t* temp = new int64_t[i * j]{5};
        for (int k = 0; k < i * j; k += 1) {
            temp[k] = 0;
        }
        for (std::ptrdiff_t row = 0; row < n_rows_; row += 1) {
            for (std::ptrdiff_t col = 0; col < n_cols_; col += 1) {
                temp[row * j + col] = this->at(row, col);
            }
        }
        n_rows_ = i;
        n_cols_ = j;
        delete[] values_;
        values_ = temp;
        temp = nullptr;
    }
}
