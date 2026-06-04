#include <pybind11/pybind11.h>

#include <linalg/Matrix.hpp>

namespace py = pybind11;


// template<size_t H, size_t W>
// void bindIntMatrix(py::module_& m) {
//     using M = Matrix<int, H, W>;
//     py::class_<M>(m)
//         .def(py::init<>())
//         .def("get", &M::get)
//         .def("set", &M::set)
//         .def("__repr__", &M::print)
//     ;
// }

void bindIntMatrix(py::module_& m) {
    using M = Matrix<int, 2, 2>;
    py::class_<M>(m)
        .def(py::init<>())
        // .def("get", &M::get)
        .def("set", &M::set)
        .def("__repr__", &M::print)
    ;
}

// template<size_t... Ns>
// void bind_vectors(py::module_& m, std::index_sequence<Ns...>) {
//     (bind_vector<Ns + 1>(m,
//         "Vector" + std::to_string(Ns + 1)), ...);
// }

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(linalg, m) {
    m.doc() = "A simple library for basic matrix operations.";
    m.def("add", &add, "Add two integers");


    py::class_<Matrix<int, 2, 2>>(m)
        .def(py::init<>())
        // .def("get", &Matrix<int, 2, 2>::get)
        .def("set", &Matrix<int, 2, 2>::set)
        .def("__repr__", &Matrix<int, 2, 2>::print)
    ;
    // bindIntMatrix(m);
    // for (size_t i = 0; i < 20; ++i) {
    //     for (size_t j = 0; j < 20; ++j) {
    //         bindIntMatrix<i, j>(m);
    //     }
    // }
    //
    // bindIntMatrix<1,1>(m);
    // bindIntMatrix<2,1>(m);
    // bindIntMatrix<1,2>(m);
    // bindIntMatrix<2,2>(m);


}
