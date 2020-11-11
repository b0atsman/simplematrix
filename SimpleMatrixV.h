//
// Created by boatsman on 05.11.2020.
//

#ifndef SIMPLEMATRIX_SIMPLEMATRIX_V_H
#define SIMPLEMATRIX_SIMPLEMATRIX_V_H

#include <iostream>
#include <vector>
#include <memory>

#include "SimpleMatrixIteratorV.h"

class SimpleMatrix {
private:
    size_t rowCount;
    size_t colCount;
    size_t elementCount;

    std::vector<int> data;

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
        return iterator(&data[rowCount * colCount]);
    }

    const_iterator begin() const
    {
        return const_iterator(&data[0]);
    }

    const_iterator end() const
    {
        return const_iterator(&data[rowCount * colCount]);
    }

    // basic constructor
    SimpleMatrix(size_t m = 1, size_t n = 1) :
        rowCount(m),
        colCount(n),
        elementCount(m * n)
    {
        data.resize(elementCount);
    }

    // initializing constructor
    SimpleMatrix(size_t m, size_t n, const std::initializer_list<int> &values) : SimpleMatrix(m, n) {
        if (values.size() <= elementCount)
            // copy all values, leaving leading zeroes in the buffer
            std::copy(values.begin(), values.end(), data.begin());
        else
            // copy values partially, to fulfill the buffer
            std::copy(values.begin(), values.begin() + elementCount, data.begin());
    }

    // copy constructor
    SimpleMatrix(const SimpleMatrix& other)
      : SimpleMatrix(other.rowCount, other.colCount)
    {
        std::copy(other.data.begin(), other.data.end(), data.begin());
    }

    // copy = operator
    SimpleMatrix& operator= (const SimpleMatrix &other)
    {
        if (&other != this) {
            rowCount = other.rowCount;
            colCount = other.colCount;
            elementCount = other.elementCount;
            data.resize(elementCount);
            std::copy(other.data.begin(), other.data.end(), data.begin());
        }
        return *this;
    }

    // move constructor
    SimpleMatrix(SimpleMatrix&& other) : SimpleMatrix(other.rowCount, other.colCount)
    {
        data = std::move(other.data);

        // clean up other
        other.rowCount = 0;
        other.colCount = 0;
        other.elementCount = 0;
    }

    // move = operator
    SimpleMatrix& operator= (SimpleMatrix &&other)
    {
        if (&other != this) {
            data = std::move(other.data);

            // clean up other
            other.rowCount = 0;
            other.colCount = 0;
            other.elementCount = 0;
        }
        return *this;
    }

    // index operator (non-const)
    int& operator[] (const size_t index)
    {
        if (index >= elementCount)
            throw std::runtime_error("SimpleMatrix::operator[] error: index overflow!\n");;

        return data[index];
    }

    // index operator (const)
    const int& operator[] (const size_t index) const
    {
        if (index >= elementCount)
            throw std::runtime_error("SimpleMatrix::operator[] error: index overflow!\n"); ;

        return data[index];
    }

    // sum operator
    SimpleMatrix operator+ (const SimpleMatrix &other)
    {
        if ((rowCount != other.rowCount) || (colCount != other.colCount))
            throw std::runtime_error("SimpleMatrix::operator+ error: rowCount or colCount do not match!\n");

        SimpleMatrix result = SimpleMatrix(rowCount, colCount);

        for (size_t i = 0; i < elementCount; i++)
            result[i] = data[i] + other[i];

        return result;
    }

    // concatenation operator
    SimpleMatrix operator| (const SimpleMatrix &other)
    {
        if ((rowCount != other.rowCount))
            throw std::runtime_error("SimpleMatrix::operator| error: rowCount do not match!\n");

        SimpleMatrix result = SimpleMatrix(rowCount, colCount + other.colCount);

        size_t rowIndex, colIndex;
        for (size_t i = 0; i < result.elementCount; ++i) {
            rowIndex = i / result.colCount;
            colIndex = i % result.colCount;

            if (colIndex < colCount) {
                // copy from self
                result[i] = data[rowIndex * colCount + colIndex];
            } else {
                // copy from other
                result[i] = other[rowIndex * other.colCount + colIndex - colCount];
            }
        }

        return result;
    }

    // equals operator
    friend bool operator== (const SimpleMatrix& a, const SimpleMatrix& b);

    // not equals operator
    friend bool operator!= (const SimpleMatrix& a, const SimpleMatrix& b);

    // output operator (pretty print)
    friend std::ostream& operator<< (std::ostream& out, const SimpleMatrix& m);
};

bool operator== (const SimpleMatrix& a, const SimpleMatrix& b)
{
    return ((a.rowCount == b.rowCount)
            && (a.colCount == b.colCount)
            && a.data == b.data);
}

bool operator!= (const SimpleMatrix& a, const SimpleMatrix& b)
{
    return !(a == b);
}

std::ostream& operator<< (std::ostream& out, const SimpleMatrix &m) {
    for (size_t row = 0; row < m.rowCount; ++row) {
        for (size_t col = 0; col < m.colCount; ++col) {
            out << m.data[row * m.colCount + col] << "  ";
        }
        out << std::endl;
    }

    return out;
}

#endif //SIMPLEMATRIX_SIMPLEMATRIX_V_H
