#include <linalg/vector2.hpp>

#include <cmath>

Vector2::Vector2(float x, float y)
    : x(x), y(y) {}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}