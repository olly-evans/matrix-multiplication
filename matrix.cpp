
#include "matrix.h"

#include <iostream>
#include <limits>
#include <stdexcept>

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : 
    rows(nRows), cols(nCols), elements(checkedSize(nRows, nCols)) {

    data = new int64_t[rows * cols]();
}

Matrix::~Matrix() {
    delete[] data;
}

static uint64_t checkedSize(uint64_t r, uint64_t c) {

    if (r == 0 || c == 0)
        throw std::invalid_argument("Matrix dimension must be non-zero");

    if (r > std::numeric_limits<uint64_t>::max() / c)
        throw std::overflow_error("Matrix size overflows");

    uint64_t n = r * c;
    if (n > MAX_ELEMENTS)
        throw std::length_error("Matrix too large");
    
    return n;
}

void Matrix::Print() const {

    for (uint64_t i = 0; i < elements; i++) {
        
        /* If at end of row print new-line instead of comma. */
        if ((i % cols) < cols-1) {
            std::cout << GetElement(i) << ",";
            continue;
        }
        std::cout << GetElement(i) << "\n";
    }
}

uint64_t Matrix::Size() const {
    return elements;
}

void Matrix::InsertAtIndex(int64_t value, uint64_t index) {

    if (!(index < Size()))
        std::cerr << "Index is out of matrix bounds - cannot insert." << std::endl;
    int64_t* dest = data + static_cast<int64_t>(index);
    *dest = value;
}

void Matrix::InsertAtCoord(int64_t value, uint64_t row, uint64_t col) {

    uint64_t index = row*cols + col;

    if (!(index < Size()))
        std::cerr << "Coordinate is out of matrix bounds - cannot insert." << std::endl;

    int64_t* dest = data + static_cast<int64_t>(index);
    *dest = value;
}

Matrix Matrix::operator+(const Matrix& B) const {
    
    const Matrix& A = *this;

    if (A.GetRows() != B.GetRows())
        std::cerr << "Row number mismatch - cannot add." << std::endl;

    if (A.GetCols() != B.GetCols())
        std::cerr << "Column number mismatch - cannot add." << std::endl;

    Matrix C(A.GetRows(), A.GetCols());

    for (uint64_t i = 0; i < A.elements; i++) {
        int64_t value = A.GetElement(i) + B.GetElement(i);
        C.InsertAtIndex(value, i);
    }
    
    return C;

}

Matrix Matrix::operator-(const Matrix& B) const {
    
    const Matrix& A = *this;

    if (A.GetRows() != B.GetRows())
        std::cerr << "Row number mismatch - cannot subtract." << std::endl;
    
    if (A.GetRows() != B.GetCols())
        std::cerr << "Col number mismatch - cannot subtract." << std::endl;

    Matrix C(A.GetRows(), A.GetCols());

    for (uint64_t i = 0; i < A.elements; i++) {
        int64_t value = A.GetElement(i) - B.GetElement(i);
        C.InsertAtIndex(value, i);
    }

    return C;
}

Matrix Matrix::Multiply(Matrix& B) const {
    
    const Matrix& A = *this;

    if (A.GetCols() != B.GetRows())
        std::cerr << "Matrix A must have columns equal to rows of Matrix B to multiply." << std::endl;

    Matrix C(A.GetRows(), B.GetCols());

    for (uint64_t index = 0; index < C.Size(); index++) {

        int64_t sum = 0;

        /* Filling out new matrix. Hence result dimensions. */
        const uint64_t row = index / C.GetCols();
        const uint64_t col = index % C.GetCols(); 

        /* First element index in required row/col */
        const uint64_t rowStart = row*A.GetCols();
        const uint64_t colStart = col;

        for (uint64_t i = 0; i < A.GetRows(); i++) {

            /* Incrementing over  appropriate row and column. */
            uint64_t nextRowElement = rowStart + i;
            uint64_t nextColElement = colStart + (i*B.GetCols());

            sum += A.GetElement(nextRowElement) * B.GetElement(nextColElement);
        }

        C.InsertAtIndex(sum, index);
    }
    return C;
}

uint64_t Matrix::GetRows() const {
    return rows;
}

uint64_t Matrix::GetCols() const {
    return cols;
}

int64_t Matrix::GetElement(uint64_t index) const {
    return *(data + index);
}

int main() {

    /* 3x3 and 3x3 example. */
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

    Matrix result = m1 - m2;

    std::cout << "\n";
    result.Print();

}