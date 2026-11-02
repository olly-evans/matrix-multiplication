#pragma once
#include <cstdint>

constexpr uint64_t MAX_BYTES    = 1ULL << 30;
constexpr uint64_t MAX_ELEMENTS = MAX_BYTES / sizeof(int64_t);

static uint64_t checkedSize(uint64_t r, uint64_t c);

class Matrix {
    public:

        Matrix(uint64_t rows, uint64_t cols);
        ~Matrix();

        void Print() const;
        [[nodiscard]] uint64_t Size() const;

        void InsertAtIndex(int64_t value, uint64_t index);
        void InsertAtCoord(int64_t value, uint64_t row, uint64_t col);

        Matrix operator+(const Matrix& B) const;
        
        Matrix operator-(const Matrix& B) const;
        Matrix Multiply(Matrix& B) const;

        [[nodiscard]] uint64_t GetRows() const;
        [[nodiscard]] uint64_t GetCols() const;
        [[nodiscard]] int64_t GetElement(uint64_t index) const;

    private:
        
        int64_t* data;

        uint64_t rows;
        uint64_t cols;

        uint64_t elements;
    
};