#include <catch2/catch_test_macros.hpp>
#include <linalg/Matrix.hpp>

TEST_CASE("mat_mul: zero matrix", "[matmul][edge]") {
    Matrix<int, 2, 3> A(0);      // all zeros
    Matrix<int, 3, 4> B(0);      // all zeros
    auto C = mat_mul(A, B);

    // Result must be a 2x4 zero matrix
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 4; ++j)
            REQUIRE(C[i][j] == 0);
}

TEST_CASE("mat_mul: rectangular matrices (2x3 * 3x2)", "[matmul][rect]") {
    Matrix<int, 2, 3> A(0);
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

    Matrix<int, 3, 2> B(0);
    B[0][0] = 7; B[0][1] = 8;
    B[1][0] = 9; B[1][1] = 10;
    B[2][0] = 11; B[2][1] = 12;

    auto C = mat_mul(A, B);  // yields 2x2 matrix

    // Expected:
    // row0: 1*7+2*9+3*11 = 58,  1*8+2*10+3*12 = 64
    // row1: 4*7+5*9+6*11 = 139, 4*8+5*10+6*12 = 154
    REQUIRE(C[0][0] == 58);
    REQUIRE(C[0][1] == 64);
    REQUIRE(C[1][0] == 139);
    REQUIRE(C[1][1] == 154);
}

TEST_CASE("mat_mul: multiplication by 1x1 matrix (scalar effect)", "[matmul][edge]") {
    Matrix<int, 3, 1> A(0);
    A[0][0] = 2;
    A[1][0] = 3;
    A[2][0] = 4;

    Matrix<int, 1, 2> B(0);
    B[0][0] = 5;
    B[0][1] = 6;

    auto C = mat_mul(A, B);  // 3x2 result

    REQUIRE(C[0][0] == 2*5);  REQUIRE(C[0][1] == 2*6);
    REQUIRE(C[1][0] == 3*5);  REQUIRE(C[1][1] == 3*6);
    REQUIRE(C[2][0] == 4*5);  REQUIRE(C[2][1] == 4*6);
}

TEST_CASE("mat_mul: result matrix uses default element initialisation", "[matmul][edge]") {
    // Ensure that the result is properly zeroed before accumulation
    Matrix<int, 2, 2> A(1);   // all ones
    Matrix<int, 2, 2> B(1);   // all ones
    auto C = mat_mul(A, B);

    // Each element = 1*1 + 1*1 = 2
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j)
            REQUIRE(C[i][j] == 2);
}
