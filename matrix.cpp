
#include "matrix.h"

#include <iostream>

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : 
    rows(nRows), 
    cols(nCols),
    elements(nRows*nCols) {

    //error check rows/cols.
    if (nRows < 0 || nCols < 0)
        std::cout << "Dimensions of Matrix cannot be less than zero." << "\n";

    data = new uint64_t[rows * cols]();
}

Matrix::~Matrix() {
    delete[] data;
}

void Matrix::Print() {

    for (uint64_t i = 0; i < elements; i++) {

        uint64_t element = *(data + i);
        
        if ((i % cols) < cols-1) {
            std::cout << element << ",";
            continue;
        }
        std::cout << element << "\n";
    }
}

uint64_t Matrix::Size() {
    return elements;
}

void Matrix::Insert(uint64_t value, uint64_t index) {
    uint64_t* dest = data + index;
    *dest = value;
}

void Matrix::Add(Matrix& B) {
    
    if (rows != B.GetRows())
        std::cerr << "Rows differing - cannot add.";

    if (cols != B.GetCols())
        std::cerr << "Cols differing - cannot add.";

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) + B.GetElement(i);
        Insert(value, i);
    }
}

void Matrix::Subtract(Matrix& B) {
    if (rows != B.GetRows())
        std::cerr << "Rows differing - cannot subtract.";
    
    if (cols != B.GetCols())
        std::cerr << "Cols differing - cannot subtract.";

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) - B.GetElement(i);
        Insert(value, i);
    }
}

Matrix Matrix::Multiply(Matrix& B) {
    
    if (GetCols() != B.GetRows())
        std::cerr << "Matrix A must have cols equal to rows of Matrix B to multiply.";

    Matrix result = Matrix(GetRows(), B.GetCols());

    for (uint64_t index = 0; index < result.Size(); index++) {

        uint64_t sum = 0;

        /* Filling out new matrix. Hence result dimensions. */
        const uint64_t row = index / result.GetCols(); // 2 / 2 = 1
        const uint64_t col = index % result.GetCols(); // 2 % 2 = 0

        /* First element index in required row/col */
        const uint64_t rowStart = row*GetCols();
        const uint64_t colStart = col;

        for (uint64_t i = 0; i < GetRows(); i++) {

            /* Incrementing over  appropriate row and column. */
            uint64_t nextRowElement = rowStart + i;
            uint64_t nextColElement = colStart + (i*B.GetCols());

            sum += GetElement(nextRowElement) * B.GetElement(nextColElement);
        }

        result.Insert(sum, index);
    }
    return result;
}

uint64_t Matrix::GetRows() {
    return rows;
}

uint64_t Matrix::GetCols() {
    return cols;
}

uint64_t Matrix::GetElement(uint64_t index) {
    return *(data + index);
}

int main() {

    Matrix m1(3, 3);
    Matrix m2(3, 3);
    
    m1.Insert(12, 3);
    m1.Insert(5, 0);
    m1.Insert(2, 5);

    m2.Insert(5, 0);
    m2.Insert(5, 2);

    m1.Print();
    std::cout << "\n";
    m2.Print();

    Matrix result = m1.Multiply(m2);

    std::cout << "\n";
    result.Print();

}