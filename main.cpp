#include <iostream>
#include "foo.h"

#include <pybind11/embed.h> 
#include <pybind11/pybind11.h>
#include <Python.h>

namespace py = pybind11;

/*
PYBIND11_EMBEDDED_MODULE(calc, m) {
	m.def("add", [](int i, int j) {
		return i + j;
	});
}
*/


int main()
{
	try
	{
		// run a python interpreter
		py::scoped_interpreter guard{};

		// init some python objects
		auto py_module = py::module::import("foo");	
		auto main = py::module::import("__main__");
		auto globals = py::globals();

		// map our desired callbacks 
		auto on_construct = py_module.attr("on_construct");
		auto on_process = py_module.attr("on_process");

		// serialize some data to a byte blob
		tDataBlob blob = makeStruct();
		size_t inputSize = sizeof(tDataBlob);
		char* buffer = new char[inputSize];
		memmove(buffer, &blob, inputSize);

		// call construct callback
		auto retVal = on_construct();
		if (retVal.is_none())
		{
			return 1;
		}

		std::cout
			<< "C++ sending values: "
			<< blob.intValue << ", "
			<< blob.floatValue << ", "
			<< blob.intArray[0] << ", "
			<< blob.intArray[1] << ", "
			<< blob.intArray[2] << ", "
			<< std::endl;

		// call process callback
		py::bytes result = on_process(py::bytes(buffer, inputSize));
		if (result.is_none())
		{	
			delete buffer;
			return 2;
		}
		else
		{
			// deserialize received data 
			size_t returnSize = PyBytes_Size(result.ptr());
			buffer = PyBytes_AsString(result.ptr());
			memmove(&blob, buffer, returnSize);
			std::cout 
				<< "C++ received values: "
				<< blob.intValue << ", "
				<< blob.floatValue << ", "
				<< blob.intArray[0] << ", "
				<< blob.intArray[1] << ", "
				<< blob.intArray[2] << ", "
				<< std::endl;
		}
		
		// cleanup memory
		free(buffer);
		return 0;
	}

	// catch python exceptions
	catch (const py::error_already_set& e)
	{
		std::cout << e.what() << std::endl;
		return 3;
	}
}