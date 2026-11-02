#pragma once
#include <cstdint>
#include <array>

class Matrix {
    public:

        Matrix(uint64_t rows, uint64_t cols);
        ~Matrix();

        void Print() const;
        [[nodiscard]] uint64_t Size() const;

        void InsertAtIndex(uint64_t value, uint64_t index);
        void InsertAtCoord(uint64_t value, uint64_t row, uint64_t col);

        void Add(Matrix& B);
        void Subtract(Matrix& B);
        Matrix Multiply(Matrix& B) const;

        [[nodiscard]] uint64_t GetRows() const;
        [[nodiscard]] uint64_t GetCols() const;
        [[nodiscard]] uint64_t GetElement(uint64_t index) const;

    private:
        uint64_t* data;

        uint64_t rows;
        uint64_t cols;
        uint64_t elements;
    
};