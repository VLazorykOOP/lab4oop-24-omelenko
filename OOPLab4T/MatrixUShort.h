#pragma once
#ifndef MATRIX_USHORT_H
#define MATRIX_USHORT_H

#include "VectorUShort.h"
#include <iostream>

class MatrixUShort {
protected:
    VectorUShort* UShortArray;
    int n;                     
    int size;                  
    int state;             // Код помилки: 0 - OK, 1 - вихід за межі, 2 - нестача пам'яті
    static int objectCount;     

public:
    MatrixUShort();
    MatrixUShort(int size);
    MatrixUShort(int rows, int cols);
    MatrixUShort(int rows, int cols, unsigned short value);
    MatrixUShort(const MatrixUShort& other);

    ~MatrixUShort();

    int getRows() const { return n; }
    int getCols() const { return size; }
    int getCodeError() const { return state; }
    static int getNumMatrix() { return objectCount; }

    void setState(int a) { state = a; }

    MatrixUShort& operator=(const MatrixUShort& other);

    MatrixUShort& operator++();    // Префіксний ++
    MatrixUShort operator++(int);  // Постфіксний ++
    MatrixUShort& operator--();    // Префіксний --
    MatrixUShort operator--(int);  // Постфіксний --
    bool operator!() const;
    MatrixUShort operator~() const;
    MatrixUShort operator-() const;

    MatrixUShort operator+(const MatrixUShort& other);
    MatrixUShort operator+(const unsigned short& scalar);
    MatrixUShort operator-(const MatrixUShort& other);
    MatrixUShort operator-(const unsigned short& scalar);
    MatrixUShort operator*(const MatrixUShort& other);
    VectorUShort operator*(const VectorUShort& vec);
    MatrixUShort operator*(const unsigned short& scalar);
    MatrixUShort operator/(const unsigned short& scalar);
    MatrixUShort operator%(const unsigned short& scalar);

    MatrixUShort& operator+=(const MatrixUShort& other);
    MatrixUShort& operator+=(const unsigned short& scalar);
    MatrixUShort& operator-=(const MatrixUShort& other);
    MatrixUShort& operator-=(const unsigned short& scalar);
    MatrixUShort& operator*=(const MatrixUShort& other);
    MatrixUShort& operator*=(const VectorUShort& vec);
    MatrixUShort& operator*=(const unsigned short& scalar);
    MatrixUShort& operator/=(const unsigned short& scalar);
    MatrixUShort& operator%=(const unsigned short& scalar);


    bool operator==(const MatrixUShort& other);
    bool operator!=(const MatrixUShort& other);
    bool operator>(const MatrixUShort& other);
    bool operator>=(const MatrixUShort& other);
    bool operator<(const MatrixUShort& other);
    bool operator<=(const MatrixUShort& other);

    VectorUShort& operator[](int index);

    void operator()();

    MatrixUShort& operator>>=(const MatrixUShort& other);
    MatrixUShort& operator>>=(const unsigned short& scalar);
    MatrixUShort& operator<<=(const MatrixUShort& other);
    MatrixUShort& operator<<=(const unsigned short& scalar);

    friend std::istream& operator>>(std::istream& is, MatrixUShort& matrix);
    friend std::ostream& operator<<(std::ostream& os, const MatrixUShort& matrix);
    friend MatrixUShort operator>>(const MatrixUShort& matrix, unsigned short shift);
    friend MatrixUShort operator<<(const MatrixUShort& matrix, unsigned short shift);
};

#endif