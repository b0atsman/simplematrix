//
// Created by boatsman on 06.11.2020.
//

#ifndef SIMPLEMATRIX_SIMPLEMATRIXITERATOR_V_H
#define SIMPLEMATRIX_SIMPLEMATRIXITERATOR_V_H

#include <iterator>

template<typename ValueType>
class SimpleMatrixIterator: public std::iterator<std::input_iterator_tag, ValueType>
{
    friend class SimpleMatrix;
private:
    SimpleMatrixIterator(ValueType* p);

public:
    SimpleMatrixIterator(const SimpleMatrixIterator &it);

    bool operator!=(SimpleMatrixIterator const& other) const;
    bool operator==(SimpleMatrixIterator const& other) const;
    typename SimpleMatrixIterator::reference operator*() const;
    SimpleMatrixIterator& operator++();

private:
    ValueType* p;
};

template<typename ValueType>
SimpleMatrixIterator<ValueType>::SimpleMatrixIterator(ValueType *p) : p(p) { }

template<typename ValueType>
SimpleMatrixIterator<ValueType>::SimpleMatrixIterator(const SimpleMatrixIterator& it) : p(it.p) { }

template<typename ValueType>
bool SimpleMatrixIterator<ValueType>::operator!=(SimpleMatrixIterator const& other) const
{
    return p != other.p;
}

template<typename ValueType>
bool SimpleMatrixIterator<ValueType>::operator==(SimpleMatrixIterator const& other) const
{
    return p == other.p;
}

template<typename ValueType>
typename SimpleMatrixIterator<ValueType>::reference SimpleMatrixIterator<ValueType>::operator*() const
{
    return *p;
}

template<typename ValueType>
SimpleMatrixIterator<ValueType> &SimpleMatrixIterator<ValueType>::operator++()
{
    ++p;
    return *this;
}

#endif //SIMPLEMATRIX_SIMPLEMATRIXITERATOR_V_H
