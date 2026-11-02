
#include <cstdint>
#include <array>

class Matrix {

    private:
        uint64_t* data;

        uint64_t rows;
        uint64_t cols;
        uint64_t elements;
    
    public:

        Matrix(uint64_t rows, uint64_t cols);
        ~Matrix();

        void Insert(uint64_t value, uint64_t index);

        uint64_t* Data();
        uint64_t Size();

        uint64_t GetElement(uint64_t index);

        void Print();


        void Add(Matrix& added);
        void Subtract(Matrix& subtract);
        Matrix Multiply(Matrix& multiply);

        uint64_t GetRows();
        uint64_t GetCols();
};