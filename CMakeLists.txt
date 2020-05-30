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
