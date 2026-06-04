#include <cassert>
#include <iostream>
#include <ostream>

#include "linalg_salvat/vector2.h"

int main() {
    Vector2 v(3.0f, 4.0f);

    assert(v.length() == 5.0f);

    std::cout << "All tests have passed. Hooray!!!" << std::endl;
}