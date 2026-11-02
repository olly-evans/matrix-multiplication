
#include "matrix.h"

#include <iostream>

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : 
    rows(nRows), 
    cols(nCols),
    elements(nRows*nCols) {

    if (nRows < 0 || nCols < 0)
        std::cerr << "Dimension of Matrix cannot be less than zero." << std::endl;

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

void Matrix::InsertAtIndex(uint64_t value, uint64_t index) {

    if (!(index < Size()))
        std::cerr << "Index is out of matrix bounds - cannot insert." << std::endl;
    uint64_t* dest = data + index;
    *dest = value;
}

void Matrix::InsertAtCoord(uint64_t value, uint64_t row, uint64_t col) {

    uint64_t index = row*cols + col;

    if (!(index < Size()))
        std::cerr << "Coordinate is out of matrix bounds - cannot insert." << std::endl;

    uint64_t* dest = data + index;
    *dest = value;
}

void Matrix::Add(Matrix& B) {
    
    if (rows != B.GetRows())
        std::cerr << "Row number mismatch - cannot add." << std::endl;

    if (cols != B.GetCols())
        std::cerr << "Column number mismatch - cannot add." << std::endl;

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) + B.GetElement(i);
        InsertAtIndex(value, i);
    }
}

void Matrix::Subtract(Matrix& B) {
    if (rows != B.GetRows())
        std::cerr << "Row number mismatch - cannot subtract." << std::endl;
    
    if (cols != B.GetCols())
        std::cerr << "Col number mismatch - cannot subtract." << std::endl;

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) - B.GetElement(i);
        InsertAtIndex(value, i);
    }
}

Matrix Matrix::Multiply(Matrix& B) {
    
    if (GetCols() != B.GetRows())
        std::cerr << "Matrix A must have columns equal to rows of Matrix B to multiply." << std::endl;

    Matrix result(GetRows(), B.GetCols());

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

        result.InsertAtIndex(sum, index);
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
    
    m1.InsertAtCoord(3, 0, 0);
    m1.InsertAtCoord(5, 2, 0);
    m1.InsertAtCoord(2, 1, 1);

    m2.InsertAtCoord(5, 0, 0);
    m2.InsertAtCoord(5, 2, 2);

    m1.Print();
    std::cout << "\n";
    m2.Print();

    Matrix result = m1.Multiply(m2);

    std::cout << "\n";
    result.Print();

}