#include "matrix.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Commutative Law of Addition: A+B = B+A", "[matrix][algebra]") {

    uint64_t n = 2;
    Matrix A(n, n);
    Matrix B(n, n);

    Matrix left = A + B;
    Matrix right = B + A;

    REQUIRE(left == right);
}

TEST_CASE("Associative Law of Addition: A + (B + C) = (A + B) + C", "[matrix][algebra]") {
    
    uint64_t n = 5;
    Matrix A(n, n);
    Matrix B(n, n);
    Matrix C(n, n);

    Matrix left = A + (B + C);
    Matrix right = (A + B) + C;

    REQUIRE(left == right);
}

TEST_CASE("Distributive Law of a Scalar over Matrices: c(A + B) = cA + cB", "[matrix][algebra]") {
    
    uint64_t n = 5;
    Matrix A(n, n);
    Matrix B(n, n);
    Matrix C(n, n);

    uint64_t scalar = 8;

    Matrix left = scalar*(A+B);
    Matrix right = scalar*A + scalar*B;

    REQUIRE(left == right);
}

TEST_CASE("Right Distributive law: A(B+C) = AB + AC", "[matrix][algebra]") {

    Matrix A(2, 2);
    Matrix B(2, 2);
    Matrix C(2, 2);

    A.Randomize();
    B.Randomize();
    C.Randomize();

    Matrix left = A * (B + C);
    Matrix right = (A*B) + (A*C);

    REQUIRE(left == right);
}

TEST_CASE("Left Distributive law: (B+C)A = BA + CA", "[matrix][algebra]") {

    Matrix A(2, 2);
    Matrix B(2, 2);
    Matrix C(2, 2);

    A.Randomize();
    B.Randomize();
    C.Randomize();

    Matrix left = (B + C)*A;
    Matrix right = (B*A) + (C*A);

    REQUIRE(left == right);
}

TEST_CASE("Non-commutativity: AB != BA", "[matrix][algebra]") {

    Matrix A(3, 5);
    Matrix B(5, 3);

    A.Randomize();
    B.Randomize();

    Matrix left = A*B;
    Matrix right = B*A;

    REQUIRE_FALSE(left == right);
}

TEST_CASE("Associativity: A(BC) = (AB)C", "[matrix][algebra]") {

    Matrix A(2, 2);
    Matrix B(2, 2);
    Matrix C(2, 2);

    A.Randomize();
    B.Randomize();
    C.Randomize();

    Matrix left = A*(B*C);
    Matrix right = (A*B)*C;

    REQUIRE(left == right);
}

TEST_CASE("Identity matrix: AI = IA = A", "[matrix][algebra]") {

    uint64_t n = 5;
    Matrix A(n, n);
    Matrix I = Matrix::Identity(n);

    Matrix left = A*I;
    Matrix middle = I*A;

    REQUIRE(left == A);
    REQUIRE(middle == left);
    REQUIRE(middle == A);
}

TEST_CASE("Zero matrix product: A0 = 0A = 0", "[matrix][algebra]") {

    uint64_t n = 3;
    Matrix A(n, n);
    Matrix Z = Matrix::Zeroes(n);

    Matrix left = A*Z;
    Matrix middle = Z*A;

    REQUIRE(left == middle);
    REQUIRE(left == Z);
    REQUIRE(middle == Z);
}

TEST_CASE("Incompatible dimensions: AB may not be possible", "[matrix][algebra]") {

    Matrix A(3, 5);
    Matrix B(3, 5);

    A.Randomize();
    B.Randomize();

    REQUIRE_THROWS(A*B);
}

TEST_CASE("Zero divisors: AB = 0 does not imply A = 0 or B = 0", "[matrix][algebra]") {

    uint64_t n = 2;
    Matrix A(n, n);
    Matrix B(n, n);
    Matrix Z = Matrix::Zeroes(n);

    A.InsertAtCoord(1, 0, 0);
    B.InsertAtCoord(1, 1, 1);

    REQUIRE_FALSE(A == Z); 
    REQUIRE_FALSE(B == Z); 
    REQUIRE(A * B == Z);
}