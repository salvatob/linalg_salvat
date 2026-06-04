#pragma once

#include <cstddef>
#include <memory>
#include <iostream>

// forward declaration of the
template<typename Element, size_t Height, size_t Width>
class Matrix;

// declare operators before the Matrix class so we can easily mark them as friend
template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator+(
    const Matrix<Element, Height, Width>& matrix,
    const Element& increment
    );

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator*(
    const Matrix<Element, Height, Width>& matrix,
    const Element& factor
    );

template<typename Element, size_t Height, size_t Width>
Matrix<Element, Height, Width> operator+(
    const Matrix<Element, Height, Width>& matrix_1,
    const Matrix<Element, Height, Width>& matrix_2
    );


template<typename Element, size_t M, size_t N, size_t P>
Matrix<Element, M, P> mat_mul(
    const Matrix<Element, M, N>& matrix_1,
    const Matrix<Element, N, P>& matrix_2
    );



template<typename Element, size_t Height, size_t Width>
class Matrix {
    std::shared_ptr<std::array<Element, Height * Width>> data_;

    class Request;

public:
    explicit Matrix(const Element& value = 0);

    Element& get(size_t row, size_t column);
    const Element& get(size_t row, size_t column) const;
    void set(size_t row, size_t column, const Element& value);

    Request operator[](size_t rowIndex);
    const Request operator[](size_t rowIndex) const;

    void print(std::ostream& stream = std::cout) const;
    Matrix& operator++();
    Matrix operator++(int);

    void separateFromOtherReferences();

    friend Matrix operator+<>(const Matrix& matrix, const Element& increment);
    friend Matrix operator*<>(const Matrix& matrix, const Element& factor);
    friend Matrix operator+<>(const Matrix& matrix_1, const Matrix& matrix_2);


    template<typename E, size_t H, size_t D, size_t W>
        friend Matrix<E, H, W> operator*(
            const Matrix<E, H, D>& matrix_1,
            const Matrix<E, D, W>& matrix_2
        );
};



template<typename Element, size_t Height, size_t Width>
class Matrix<Element, Height, Width>::Request {
    const Matrix &matrix_;
    size_t row_;
    Request(const Matrix &matrix, size_t row) ;

    friend Matrix;
public:
    const Element& operator[](size_t columnIndex) const;
    Element& operator[](size_t columnIndex);
};


template<typename Element, std::size_t Height, std::size_t Width>
std::ostream & operator<<(std::ostream &stream, const Matrix<Element, Height, Width> &matrix);

#include "../../src/Matrix.tpp"
