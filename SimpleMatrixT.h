//
// Created by boatsman on 05.11.2020.
//

#ifndef SIMPLEMATRIX_SIMPLEMATRIX_T_H
#define SIMPLEMATRIX_SIMPLEMATRIX_T_H

#include <iostream>
#include <initializer_list>
#include <memory>
#include <assert.h>

#include "SimpleMatrixIteratorT.h"

template<size_t rows, size_t cols, typename T>
class SimpleMatrix;

template <int rows, int cols, typename T>
bool operator == (const SimpleMatrix<rows, cols, T>& a, const SimpleMatrix<rows, cols, T>& b);

template <int rows, int cols, typename T>
bool operator != (const SimpleMatrix<rows, cols, T>& a, const SimpleMatrix<rows, cols, T>& b);

template<size_t rows, size_t cols, typename T>
std::ostream& operator << (std::ostream &out, const SimpleMatrix<rows, cols, T> &m);

template<size_t rows, size_t cols, typename T>
class SimpleMatrix
{
    std::unique_ptr<T[]> data;

public:
    // iterators
    typedef SimpleMatrixIterator<int> iterator;
    typedef SimpleMatrixIterator<const int> const_iterator;

    iterator begin()
    {
        return iterator(&data[0]);
    }

    iterator end()
    {
        return iterator(&data[rows * cols]);
    }

    const_iterator begin() const
    {
        return const_iterator(&data[0]);
    }

    const_iterator end() const
    {
        return const_iterator(&data[rows * cols]);
    }

    using Self = SimpleMatrix<rows, cols, T>;

    SimpleMatrix(): data(new T[rows * cols]) {}

    SimpleMatrix(const std::initializer_list<T> &values) : data(new T[rows * cols])
    {
        assert(values.size() == rows * cols);

        std::copy(values.begin(), values.end(), begin());
    }

    SimpleMatrix(const Self& other) {
        data = std::unique_ptr<T[]>(new T[rows * cols]);
        std::copy(other.begin(), other.end(), begin());
    }

    SimpleMatrix(Self&& other) {
        data = std::move(other.data);
    }

    SimpleMatrix& operator = (const Self& other) {
        if (&other != this) {
            assert(data != nullptr && other.data != nullptr);
            data = std::unique_ptr<T[]>(new T[rows * cols]);
            std::copy(other.begin(), other.end(), begin());
        }
        return *this;
    }

    SimpleMatrix& operator = (Self&& other) {
        if (&other != this) {
            assert(data != nullptr && other.data != nullptr);
            data = std::move(other.data);
        }
        return *this;
    }

    // index operator (non-const)
    T& operator[] (const size_t index)
    {
        assert(index < rows * cols);
        return data[index];
    }

    // index operator (const)
    const T& operator[] (const size_t index) const
    {
        assert(index < rows * cols);

        return data[index];
    }

    // sum operator
    SimpleMatrix operator + (const Self& other)
    {
        assert(data != nullptr && other.data != nullptr);

        Self result;
        for (size_t i = 0; i < rows * cols; ++i)
            result[i] = data[i] + other[i];

        return result;
    }

    // concatenation operator
    template<size_t othercols>
    SimpleMatrix<rows, cols + othercols, T> operator | (const SimpleMatrix<rows, othercols, T>& other) {
        assert(data != nullptr);

        SimpleMatrix<rows, cols + othercols, T> result;
        size_t rowIndex, colIndex;
        for (size_t i = 0; i < rows * (cols + othercols) ; ++i) {
            rowIndex = i /  (cols + othercols);
            colIndex = i % (cols + othercols);

            if (colIndex < cols) {
                // copy from self
                result[i] = data[rowIndex * cols + colIndex];
            } else {
                // copy from other
                result[i] = other[rowIndex * othercols + colIndex - cols];
            }
        }

        return result;
    }

    // equals operator
    friend bool operator == <rows, cols, T> (const Self& a, const Self& b);

    // not equals operator
    friend bool operator != <rows, cols, T> (const Self& a, const Self& b);

    // output operator (pretty print)
    friend std::ostream& operator << <rows, cols, T> (std::ostream& out, const Self& m);
};

template<size_t rows, size_t cols, typename T>
bool operator == (const SimpleMatrix<rows, cols, T>& a, const SimpleMatrix<rows, cols, T>& b) {
    //assert(a.data != nullptr && b.data != nullptr);
    for (int i = 0; i < rows * cols; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

template<size_t rows, size_t cols, typename T>
bool operator != (const SimpleMatrix<rows, cols, T>& a, const SimpleMatrix<rows, cols, T>& b) {
    return !(a == b);
}

template<size_t rows, size_t cols, typename T>
std::ostream& operator << (std::ostream &out, const SimpleMatrix<rows, cols, T> &m) {
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            out << m.data[row * cols + col] << "  ";
        }
        out << std::endl;
    }
    return out;
}

#endif //SIMPLEMATRIX_SIMPLEMATRIX_T_H
