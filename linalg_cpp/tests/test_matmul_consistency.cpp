#include <catch2/catch_test_macros.hpp>
#include <linalg/Matrix.hpp>

// Helper: dot product of row i from A and column j from B
template<typename Element, size_t M, size_t N, size_t P>
Element manual_dot(const Matrix<Element, M, N>& A,
                   const Matrix<Element, N, P>& B,
                   size_t i, size_t j) {
    Element sum = 0;
    for (size_t k = 0; k < N; ++k)
        sum += A[i][k] * B[k][j];
    return sum;
}

TEST_CASE("mat_mul: consistency with manual dot product (random values)", "[matmul][consistency]") {
    // Fixed non‑random but arbitrary values for reproducibility
    Matrix<int, 3, 4> A(0);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 4; ++j)
            A[i][j] = i * 10 + j + 1;  // 1..12

    Matrix<int, 4, 5> B(0);
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 5; ++j)
            B[i][j] = (i + 1) * (j + 1); // 1,2,3,4,5; 2,4,6,8,10; ...

    auto C = mat_mul(A, B);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            REQUIRE(C[i][j] == manual_dot(A, B, i, j));
        }
    }
}
