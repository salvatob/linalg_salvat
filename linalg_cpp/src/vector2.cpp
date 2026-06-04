#include "linalg_salvat/vector2.h"

#include <cmath>

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
}

float Vector2::length() const
{
    return std::sqrt(x * x + y * y);
}