
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

uint64_t Matrix::GetRows() {
    return rows;
}

uint64_t Matrix::GetCols() {
    return cols;
}

uint64_t* Matrix::Data() {
    return data;
}

uint64_t Matrix::GetElement(uint64_t index) {
    return *(data + index);
}

void Matrix::Add(Matrix& added) {
    
    if (rows != added.GetRows())
        std::cerr << "Rows differing - cannot add.";

    if (cols != added.GetCols())
        std::cerr << "Cols differing - cannot add.";

    for (int i = 0; i < rows*cols; i++) {

        uint64_t value = GetElement(i) + added.GetElement(i);
        Insert(value, i);
    }
}

void Matrix::Insert(uint64_t value, uint64_t index) {
    uint64_t* dest = data + index;
    *dest = value;
}

int main() {

    Matrix m1(3, 3);
    Matrix m2(3, 3);

    m1.Insert(5, 0);
    m2.Insert(4, 0);

    m1.Add(m2);
    m1.Print();

}