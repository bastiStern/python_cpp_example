#include "foo.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
	return i + j;
}

PYBIND11_MODULE(bar, m) {
	m.doc() = "pybind11 example plugin";

	m.def("add", &add, "mimimimimi");
}
