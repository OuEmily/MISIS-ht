#pragma once
#ifndef MATRIXS_MATRIXS_HPP_20230317
#define MATRIXS_MATRIXS_HPP_20230317

#include<vector>
#include<sstream>

//const std::exception out_of_range("Error: Out of range");

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

public:
    explicit MatrixS(const SizeType& size={0,0});
    MatrixS(const std::ptrdiff_t row, const std::ptrdiff_t col);


    ~MatrixS() {
        {
            delete[] values_;
            values_ = nullptr;
        }
    }

    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    int64_t& at(const SizeType& elem);
    const int64_t& at(const SizeType& elem) const;
    int64_t& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    const int64_t& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    
    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    const SizeType& ssize() const noexcept {
        return { n_rows_, n_cols_ };
    }

    std::ptrdiff_t nRows() const {
        return n_rows_;
    }
    std::ptrdiff_t nCols() const {
        return n_cols_;
    }
private:
    std::ptrdiff_t n_rows_ = { 0 };
    std::ptrdiff_t n_cols_ = { 0 };
    //ArrayT<int64_t> values_;
    int64_t* values_ = { nullptr };

};

#endif
