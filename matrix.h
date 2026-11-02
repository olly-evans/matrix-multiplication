#pragma once

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

constexpr uint64_t MAX_BYTES    = 1ULL << 30;
constexpr uint64_t MAX_ELEMENTS = MAX_BYTES / sizeof(int64_t);

constexpr int64_t MAX_RANDOM_ELEMENT = 10;

static uint64_t CheckedSize(uint64_t r, uint64_t c);

class Matrix {
    public:

        Matrix(uint64_t rows, uint64_t cols);
        
        static Matrix Identity(uint64_t n);
        static Matrix Zeroes(uint64_t n);

        ~Matrix();

        void Print() const;
        [[nodiscard]] uint64_t Size() const;

        void InsertAtIndex(int64_t value, uint64_t index);
        void InsertAtCoord(int64_t value, uint64_t row, uint64_t col);

        Matrix operator+(const Matrix& B) const;
        Matrix operator-(const Matrix& B) const;
        Matrix operator*(const Matrix& B) const;
        bool operator==(const Matrix& B) const;

        [[nodiscard]] uint64_t GetRows() const;
        [[nodiscard]] uint64_t GetCols() const;
        [[nodiscard]] int64_t GetElement(uint64_t index) const;

        void Randomize();

    private:
        
        int64_t* data;

        uint64_t rows;
        uint64_t cols;

        uint64_t elements;
    
};