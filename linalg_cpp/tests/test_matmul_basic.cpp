#include <catch2/catch_test_macros.hpp>

#include <linalg/Matrix.hpp>

#include "catch2/catch_approx.hpp"

TEST_CASE("mat_mul: 1x1 matrices", "[matmul]")
{
    Matrix<int, 1, 1> A(5);
    Matrix<int, 1, 1> B(3);
    auto C = mat_mul(A, B);

    REQUIRE(C[0][0] == 15);
}

TEST_CASE("mat_mul: 2x2 matrices (integers)", "[matmul]") {
    Matrix<int, 2, 2> A(0);
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    Matrix<int, 2, 2> B(0);
    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    auto C = mat_mul(A, B);

    // Expected: [[19, 22], [43, 50]]
    REQUIRE(C[0][0] == 19);
    REQUIRE(C[0][1] == 22);
    REQUIRE(C[1][0] == 43);
    REQUIRE(C[1][1] == 50);
}

TEST_CASE("mat_mul: 3x3 identity multiplication", "[matmul]") {
    Matrix<int, 3, 3> I(0);
    for (size_t i = 0; i < 3; ++i)
        I[i][i] = 1;

    Matrix<int, 3, 3> M(0);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            M[i][j] = i * 3 + j + 1;  // 1..9

    auto C1 = mat_mul(I, M);
    auto C2 = mat_mul(M, I);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            REQUIRE(C1[i][j] == M[i][j]);
            REQUIRE(C2[i][j] == M[i][j]);
        }
    }
}

TEST_CASE("mat_mul: floating point types", "[matmul]") {
    Matrix<double, 2, 2> A(0.0);
    A[0][0] = 1.5; A[0][1] = 2.5;
    A[1][0] = 3.5; A[1][1] = 4.5;

    Matrix<double, 2, 2> B(0.0);
    B[0][0] = 0.5; B[0][1] = 1.0;
    B[1][0] = 1.5; B[1][1] = 2.0;

    auto C = mat_mul(A, B);

    REQUIRE(C[0][0] == Catch::Approx(1.5*0.5 + 2.5*1.5).epsilon(1e-12));
    REQUIRE(C[0][1] == Catch::Approx(1.5*1.0 + 2.5*2.0));
    REQUIRE(C[1][0] == Catch::Approx(3.5*0.5 + 4.5*1.5));
    REQUIRE(C[1][1] == Catch::Approx(3.5*1.0 + 4.5*2.0));
}
