cmake_minimum_required(VERSION 3.3)

project(PyModule)

find_package(PythonLibs 3.0 REQUIRED)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

set (target_name "module_func")
add_library(${target_name}   SHARED
	src/func.cpp
  src/common.cpp
)

target_link_libraries(${target_name} 
  ${PYTHON_LIBRARY}
)
set_target_properties(${target_name}  PROPERTIES SUFFIX ".pyd")

find_package(Eigen3 REQUIRED 3.3.0)
message(STATUS "find eigen3 from " ${Eigen3_DIR})
message(STATUS "Found required Eigen: "
  "Eigen version ${Eigen3_VERSION} in ${EIGEN3_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIRS})
set (target_name "module_class")
add_library(${target_name}   SHARED
	src/class.cpp
  src/common.cpp
)

target_link_libraries(${target_name} 
  ${PYTHON_LIBRARY}
)
set_target_properties(${target_name}  PROPERTIES SUFFIX ".pyd")

add_subdirectory(PythonExtention)