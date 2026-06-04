#include <pybind11/pybind11.h>

#include <linalg/vector2.hpp>

namespace py = pybind11;

PYBIND11_MODULE(linalg, m)
{
    py::class_<Vector2>(m, "Vector2")
        .def(py::init<float, float>())
        .def("length", &Vector2::length)
        .def_readwrite("x", &Vector2::x)
        .def_readwrite("y", &Vector2::y);
}
