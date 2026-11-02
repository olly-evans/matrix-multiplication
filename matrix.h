
#include <cstdint>
#include <array>

class Matrix {

    private:
        uint64_t* data;

        uint64_t rows;
        uint64_t cols;
    
    public:

        Matrix(uint64_t rows, uint64_t cols);
        ~Matrix();

        uint64_t GetRows();
        uint64_t GetCols();

        uint64_t* Data();

        uint64_t GetElement(uint64_t index);

        void Print();

        void Insert(uint64_t value, uint64_t index);

        void Add(Matrix& added);
        Matrix Subtract(Matrix subtracted);

        Matrix Multiply(Matrix multiplied);


};