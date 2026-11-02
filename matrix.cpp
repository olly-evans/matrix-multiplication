#include "matrix.h"

Matrix::Matrix(uint64_t nRows, uint64_t nCols) : 
    rows(nRows), cols(nCols), elements(CheckedSize(nRows, nCols)) {

    data = new int64_t[rows * cols]();
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix Matrix::Identity(uint64_t n) {
    Matrix I(n, n);
    int64_t value = static_cast<int64_t>(1);

    for (uint64_t i = 0; i < n; i++)
        I.InsertAtCoord(value, i, i);
    return I;
}

Matrix Matrix::Zeroes(uint64_t n) {
    Matrix Z(n, n);
    int64_t value = static_cast<int64_t>(0);

    for (uint64_t i = 0; i < n; i++)
        Z.InsertAtCoord(value, i, i);

    return Z;
}

void Matrix::Randomize() {

    for (uint64_t i = 0; i < Size(); i++) {
        int64_t num = rand() % (MAX_RANDOM_ELEMENT + 1);
        InsertAtIndex(num, i);
    }
}

uint64_t CheckedSize(uint64_t r, uint64_t c) {

    if (r == 0 || c == 0)
        throw std::invalid_argument("Matrix dimension must be non-zero");

    if (r > std::numeric_limits<uint64_t>::max() / c)
        throw std::overflow_error("Matrix size overflows");

    uint64_t n = r * c;
    if (n > MAX_ELEMENTS)
        throw std::length_error("Matrix too large");
    
    return n;
}

Matrix operator*(int64_t scalar, const Matrix& M) {
    Matrix R(M.GetRows(), M.GetCols());

    for (uint64_t i = 0; i < R.Size(); ++i) {
        R.InsertAtIndex(scalar*M.At(i), i);
    }
    return R;
}

Matrix operator*(const Matrix& M, int64_t scalar) {
    return scalar * M;
}

void Matrix::Print() const {

    for (uint64_t i = 0; i < elements; i++) {
        
        /* If at end of row print new-line instead of comma. */
        if ((i % cols) < cols-1) {
            std::cout << At(i) << ",";
            continue;
        }
        std::cout << At(i) << "\n";
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
        int64_t value = A.At(i) + B.At(i);
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
        int64_t value = A.At(i) - B.At(i);
        C.InsertAtIndex(value, i);
    }

    return C;
}

Matrix Matrix::operator*(const Matrix& B) const {
    
    const Matrix& A = *this;

    if (A.GetCols() != B.GetRows())
        throw std::invalid_argument("Matrix A must have columns equal to rows of Matrix B to multiply.");

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

            sum += A.At(nextRowElement) * B.At(nextColElement);
        }

        C.InsertAtIndex(sum, index);
    }
    return C;
}

bool Matrix::operator==(const Matrix& B) const {
    
    const Matrix& A = *this;

    if (A.GetCols() != B.GetCols() || A.GetRows() != B.GetRows())
        return false;

    for (uint64_t i = 0; i < Size(); i++) {
        if (A.At(i) != B.At(i))
            return false;
    }

    return true;
}

uint64_t Matrix::GetRows() const {
    return rows;
}

uint64_t Matrix::GetCols() const {
    return cols;
}

int64_t Matrix::At(uint64_t index) const {
    return *(data + index);
}