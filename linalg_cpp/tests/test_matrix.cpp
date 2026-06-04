
#include <linalg/Matrix.hpp>


#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vector2 length works correctly") {
    Matrix<int,1,1> m(69);

    REQUIRE(m[0][0] == 9);
}
