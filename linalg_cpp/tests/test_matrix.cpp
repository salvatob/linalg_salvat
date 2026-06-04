
#include <linalg/Matrix.hpp>


#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector2 length works correctly") {
    Matrix<int,1,1> m(3);
    Matrix<int,1,1> n(23);

    auto r = mat_mul(m,n);

    REQUIRE(r[0][0] == 69);
}
