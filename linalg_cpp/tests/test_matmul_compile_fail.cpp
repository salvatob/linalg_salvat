#include <type_traits>
#include "linalg/Matrix.hpp"

// ---------- Helper: is_matrix_addition_possible ----------
template<typename, typename, typename = void>
struct can_add_matrices : std::false_type {};

template<typename M1, typename M2>
struct can_add_matrices<M1, M2,
    std::void_t<decltype(std::declval<M1>() + std::declval<M2>())>>
    : std::true_type {};

// ---------- Helper: is_mat_mul_possible ----------
template<typename, typename, typename = void>
struct can_mat_mul : std::false_type {};

template<typename M1, typename M2>
struct can_mat_mul<M1, M2,
    std::void_t<decltype(mat_mul(std::declval<M1>(), std::declval<M2>()))>>
    : std::true_type {};

// ---------- Tests: these are compile‑time checks ----------
// They will trigger a compilation error if the operation is incorrectly allowed.

// Addition: same dimensions => must be allowed
static_assert( can_add_matrices<Matrix<int,2,3>, Matrix<int,2,3>>::value,
    "Addition of identically sized matrices must compile");

// Addition: different heights => must NOT compile
static_assert( !can_add_matrices<Matrix<int,2,3>, Matrix<int,3,3>>::value,
    "Addition of matrices with different heights should be impossible");

// Addition: different widths => must NOT compile
static_assert( !can_add_matrices<Matrix<int,2,3>, Matrix<int,2,4>>::value,
    "Addition of matrices with different widths should be impossible");

// Multiplication: valid inner dimension (3 == 3) => must compile
static_assert( can_mat_mul<Matrix<int,2,3>, Matrix<int,3,4>>::value,
    "mat_mul with matching inner dimension must compile");

// Multiplication: inner dimension mismatch => must NOT compile
static_assert( !can_mat_mul<Matrix<int,2,3>, Matrix<int,4,5>>::value,
    "mat_mul with mismatched inner dimension must NOT compile");

// Multiplication: different outer dimensions but correct inner => still compiles
static_assert( can_mat_mul<Matrix<int,5,2>, Matrix<int,2,7>>::value,
    "mat_mul with valid inner dimension must compile regardless of outer sizes");

// Multiplication: one dimension zero? (your Matrix class likely supports zero‑size? Not needed)
// But just to show it's strict:
static_assert( !can_mat_mul<Matrix<int,2,3>, Matrix<int,2,5>>::value,
    "Inner dimension must match exactly");

// The test runner will not produce any runtime output.
// If this file compiles, all compile‑time checks passed.
