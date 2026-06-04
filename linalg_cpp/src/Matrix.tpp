#pragma once

#include <cstddef>
#include <iostream>
#include <array>
#include <memory>



template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width>::Matrix(const Element &value)
    : data_(std::make_shared<std::array<Element, Height * Width>>())
{
    data_->fill(value);
}

template<typename Element, size_t Height, size_t Width>
Element& Matrix<Element, Height, Width>::get(size_t row, size_t column) {
    separateFromOtherReferences();
    return (*data_)[row * Width + column];
}

template<typename Element, size_t Height, size_t Width>
const Element& Matrix<Element, Height, Width>::get(size_t row, size_t column) const {
    return (*data_)[row * Width + column];
}

template<typename Element, size_t Height, size_t Width>
void Matrix<Element, Height, Width>::set(size_t row, size_t column, const Element &value) {
    separateFromOtherReferences();
    (*data_)[row * Width + column] = value;
}


template<typename Element, size_t Height, size_t Width>
void Matrix<Element, Height, Width>::print(std::ostream &stream) const {
    stream << "[";
    for (size_t i = 0; i < Height; ++i) {
        if (i > 0) stream << ", ";
        stream << "[";
        for (size_t j = 0; j < Width; ++j) {
            if (j > 0) stream << ", ";
            stream << get(i, j);
        }
        stream << "]";
    }
    stream << "]";
}

///////////////////////////////////////

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> & Matrix<Element, Height, Width>::operator++() {
    separateFromOtherReferences();

    for (auto it = data_->begin(); it != data_->end(); ++it) {
        ++(*it);
    }
    return *this;
}

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> Matrix<Element, Height, Width>::operator++(int) {
    Matrix temp = Matrix(*this);
    separateFromOtherReferences();

    for (auto it = data_->begin(); it != data_->end(); ++it) {
        // ReSharper disable once CppDiscardedPostfixOperatorResult
        (*it)++;
    }

    return temp;
}

template<typename Element, size_t Height, size_t Width>
void Matrix<Element, Height, Width>::separateFromOtherReferences() {
    if (data_.use_count() > 1) {
        // create new array instance, enclose it in a shared ptr and set is at this.data_
        auto new_data = std::make_shared<std::array<Element, Height * Width>>(*data_);
        data_ = new_data;
    }
}

template<typename Element, std::size_t Height, std::size_t Width>
std::ostream & operator<<(std::ostream &stream, const Matrix<Element, Height, Width> &matrix) {
    matrix.print(stream);
    return stream;
}

//////////////////// Request Logic ///////////////////////

template <typename Element, size_t M, size_t N, size_t P>
Matrix<Element, M, P> mat_mul(const Matrix<Element, M, N>& matrix_1, const Matrix<Element, N, P>& matrix_2) {
    return matrix_1*matrix_2;
}

// constructors
template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width>::Request::Request(const Matrix &matrix, size_t row) : matrix_(
    matrix), row_(row) {}



template<typename Element, size_t Height, size_t Width>
Element& Matrix<Element, Height, Width>::Request::operator[](size_t columnIndex) {
    const_cast<Matrix&>(matrix_).separateFromOtherReferences();
    return (*matrix_.data_)[row_ * Width + columnIndex];
}


template<typename Element, size_t Height, size_t Width>
const Element & Matrix<Element, Height, Width>::Request::operator[](size_t columnIndex) const {
    return const_cast<Element &>((*matrix_.data_)[row_ * Width + columnIndex]);
}

// Matrix indexers

template<typename Element, size_t Height, size_t Width>
typename Matrix<Element, Height, Width>::Request Matrix<Element, Height, Width>::operator[](size_t rowIndex) {
    return Request(*this, rowIndex);
}

template<typename Element, size_t Height, size_t Width>
const typename Matrix<Element, Height, Width>::Request Matrix<Element, Height, Width>::operator[](size_t rowIndex) const {
    return Request(*this, rowIndex);
}

////////////////////////////////////////

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator+(const Matrix<Element, Height, Width>& matrix, const Element& increment) {
    Matrix<Element, Height, Width> copy(matrix);
    copy.separateFromOtherReferences();
    auto origin_it = matrix.data_->begin();
    auto copy_it = copy.data_->begin();
    auto copy_end = copy.data_->end();

    while (copy_it != copy_end) {
        *copy_it = (*origin_it) + increment;
        ++copy_it;
        ++origin_it;
    }
    return copy;
}

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator*(const Matrix<Element, Height, Width>& matrix, const Element& factor) {
    Matrix<Element, Height, Width> copy(matrix);
    copy.separateFromOtherReferences();
    auto origin_it = matrix.data_->begin();
    auto copy_it = copy.data_->begin();
    auto copy_end = copy.data_->end();

    while (copy_it != copy_end) {
        *copy_it = (*origin_it) * factor;
        ++copy_it;
        ++origin_it;
    }
    return copy;
}


template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator+(const Matrix<Element, Height, Width>& matrix_1, const Matrix<Element, Height, Width>& matrix_2) {
    Matrix<Element, Height, Width> result;

    auto m1_it = matrix_1.data_->begin();
    auto m2_it = matrix_2.data_->begin();
    auto result_it = result.data_->begin();
    auto result_end = result.data_->end();

    while (result_it != result_end) {
        *result_it = (*m1_it) + (*m2_it);
        ++m1_it;
        ++m2_it;
        ++result_it;
    }
    return result;
}




template<typename Element, size_t Height, size_t Depth, size_t Width>
Matrix<Element, Height, Width> operator*(
    const Matrix<Element, Height, Depth>& matrix_1,
    const Matrix<Element, Depth, Width>& matrix_2)
{
    Matrix<Element, Height, Width> result(0);  // Initialize with 0


    const Element* data1 = matrix_1.data_->data();
    const Element* data2 = matrix_2.data_->data();
    Element* result_data = result.data_->data();

    for (size_t i = 0; i < Height; ++i) {
        for (size_t k = 0; k < Depth; ++k) {
            Element a_ik = data1[i * Depth + k];
            for (size_t j = 0; j < Width; ++j) {
                result_data[i * Width + j] += a_ik * data2[k * Width + j]
                // TODO fix after running github CI job
                +100;
            }
        }
    }

    return result;
}

//
// template<typename Element, size_t M, size_t N, size_t P>
// Matrix<Element, M, P> mat_mul(const Matrix<Element, M, N>& matrix_1,
//                               const Matrix<Element, N, P>& matrix_2) {
//     // Initialize result matrix with zeros
//     Matrix<Element, M, P> result(0);
//
//     // Raw pointers for efficient access (no shared_ptr overhead)
//     const Element* a = matrix_1.data_->data();
//     const Element* b = matrix_2.data_->data();
//     Element* c = result.data_->data();
//
//     // Loop order i-k-j: optimal for row-major storage.
//     // The inner loop accumulates over j, accessing B[k][j] and C[i][j] sequentially,
//     // which maximizes cache locality.
//     for (size_t i = 0; i < M; ++i) {
//         for (size_t k = 0; k < N; ++k) {
//             Element a_ik = a[i * N + k];
//             // Skip multiplication if a_ik is zero – beneficial for sparse matrices,
//             // but adds a branch; for dense matrices the compiler may vectorize better without it.
//             // We keep it simple and rely on the compiler's optimizations.
//             for (size_t j = 0; j < P; ++j) {
//                 c[i * P + j] += a_ik * b[k * P + j];
//             }
//         }
//     }
//     return result;
// }