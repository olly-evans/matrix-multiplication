
#include "matrix.h"

#include <iostream>
#include <cstdlib>

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : 
    rows(nRows), 
    cols(nCols),
    elements(nRows*nCols) {

    //error check rows/cols.
    if (nRows < 0 || nCols < 0)
        std::cout << "Dimensions of Matrix cannot be less than zero." << "\n";

    data = static_cast<uint64_t*>(malloc(rows * cols * sizeof(*data)));
}

Matrix::~Matrix() {
    delete[] data;
}

void Matrix::Insert(uint64_t value, uint64_t index) {
    uint64_t* dest = data + index;
    *dest = value;
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

uint64_t* Matrix::Data() {
    return data;
}

uint64_t Matrix::Size() {
    return elements;
}

uint64_t Matrix::GetElement(uint64_t index) {
    return *(data + index);
}

void Matrix::Add(Matrix& add) {
    
    if (rows != add.GetRows())
        std::cerr << "Rows differing - cannot add.";

    if (cols != add.GetCols())
        std::cerr << "Cols differing - cannot add.";

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) + add.GetElement(i);
        Insert(value, i);
    }
}

void Matrix::Subtract(Matrix& subtract) {
    if (rows != subtract.GetRows())
        std::cerr << "Rows differing - cannot subtract.";
    
    if (cols != subtract.GetCols())
        std::cerr << "Cols differing - cannot subtract.";

    for (uint64_t i = 0; i < elements; i++) {
        uint64_t value = GetElement(i) - subtract.GetElement(i);
        Insert(value, i);
    }
}

Matrix Matrix::Multiply(Matrix& multiply) {
    
    if (cols != multiply.GetRows())
        std::cerr << "Matrix A must have cols equal to rows of Matrix B to multiply.";

    Matrix result = Matrix(rows, multiply.GetCols());

    for (uint64_t index = 0; index < result.Size(); index++) {

        uint64_t sum = 0;

        const uint64_t row = index / result.GetCols(); // 2 / 2 = 1
        const uint64_t col = index % result.GetCols(); // 2 % 2 = 0

        const uint64_t rowStart = row*result.GetCols();
        const uint64_t colStart = col;

        for (uint64_t i = 0; i < result.GetCols(); i++) {
            sum += GetElement(rowStart + i) * multiply.GetElement(colStart + (i*result.GetCols()));
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

int main() {

    Matrix m1(3, 3);
    Matrix m2(3, 3);
    
    m1.Insert(12, 3);
    m1.Insert(5, 0);

    m2.Insert(5, 0);
    m2.Insert(5, 2);

    m1.Print();
    std::cout << "\n";
    m2.Print();

    Matrix result = m1.Multiply(m2);

    std::cout << "\n";
    result.Print();

}