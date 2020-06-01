cmake_minimum_required (VERSION 3.0)
project (PybindMatrix)

find_package (Eigen3 REQUIRED NO_MODULE)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})
message(STATUS "python path = " ${PYTHON_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIRS})
add_library(matrix SHARED python_matrix.cc stub.cc )
#target_compile_features(matrix PRIVATE cxx_std_11)
target_link_libraries (matrix ${PYTHON_LIBRARIES} Eigen3::Eigen)