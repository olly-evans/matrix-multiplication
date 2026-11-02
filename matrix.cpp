
#include "matrix.h"

#include <iostream>
#include <cstdlib>

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : rows(nRows), cols(nCols) {

    //error check rows/cols.
    if (nRows < 0 || nCols < 0)
        std::cout << "you fucked up" << "\n";

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

    for (int i = 0; i < rows*cols; i++) {

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

uint64_t Matrix::GetElement(uint64_t index) {
    return *(data + index);
}

void Matrix::Add(Matrix& add) {
    
    if (rows != add.GetRows())
        std::cerr << "Rows differing - cannot add.";

    if (cols != add.GetCols())
        std::cerr << "Cols differing - cannot add.";

    for (int i = 0; i < rows*cols; i++) {

        uint64_t value = GetElement(i) + add.GetElement(i);
        Insert(value, i);
    }
}

void Matrix::Subtract(Matrix& subtract) {
    if (rows != subtract.GetRows())
        std::cerr << "Rows differing - cannot subtract.";
    
    if (cols != subtract.GetCols())
        std::cerr << "Cols differing - cannot subtract.";

    for (int i = 0; i < rows*cols; i++) {
        uint64_t value = GetElement(i) - subtract.GetElement(i);
        Insert(value, i);
    }
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
    
    m1.Insert(12, 6);
    m1.Insert(5, 0);
    m2.Insert(4, 0);

    m1.Subtract(m2);
    m1.Print();

}