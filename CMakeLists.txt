cmake_minimum_required(VERSION 3.10)
project(example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(pybind11 REQUIRED)
find_package(OpenCV REQUIRED)
find_package (Python COMPONENTS Interpreter Development REQUIRED)

add_executable(example main.cpp)

add_custom_command(
  TARGET example
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy ${PROJECT_SOURCE_DIR}/scripts/test.py ${PROJECT_BINARY_DIR}/test.py
  )

  add_custom_command(
  TARGET example
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy ${PROJECT_SOURCE_DIR}/assets/R.png ${PROJECT_BINARY_DIR}/R.png
  )


# this lets me include files relative to the root source directory with a <> pair
target_link_libraries(example PUBLIC pybind11::pybind11 Python::Python ${OpenCV_LIBS})

target_include_directories(example PUBLIC ${OpenCV_INCLUDE_DIRS})