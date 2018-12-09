cmake_minimum_required(VERSION 3.5)

project(sandbox)

add_subdirectory(pybind11)



add_executable(${PROJECT_NAME} main.cpp foo.cpp foo.py foo.h)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::module)
# pybind11_add_module(bar bar.cpp)