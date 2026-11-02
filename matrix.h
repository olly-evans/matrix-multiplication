#pragma once
#include <cstdint>
#include <array>

class Matrix {
    public:

        Matrix(uint64_t rows, uint64_t cols);
        ~Matrix();

        void Print();
        uint64_t Size();

        void InsertAtIndex(uint64_t value, uint64_t index);
        void InsertAtCoord(uint64_t value, uint64_t row, uint64_t col);

        void Add(Matrix& added);
        void Subtract(Matrix& subtract);
        Matrix Multiply(Matrix& multiply);

        uint64_t GetRows();
        uint64_t GetCols();
        uint64_t GetElement(uint64_t index);

    private:
        uint64_t* data;

        uint64_t rows;
        uint64_t cols;
        uint64_t elements;
    
};