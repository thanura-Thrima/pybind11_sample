# Pybind11 example for running python scripts from c++

## Introduction:
This example contain CMakelist.txt dependancies required to link pybind11 in c++. The project demostrate most simplest
but complete example of calling python module function from c++ side and how python side can access c++ side object via import.
This example also demonstrate c++ to python stl container compatibility and fast data transfering mechanism.

## Requirements:
Python3
pybind11 package
OpenCV & python-Opencv  (this is optional to example, used for demonstrate how large image can transfer between c++ and python)

## Specific instruction:
pybind can directly load python modules if module reside in system PATH. For the simplicity user need to add execution directory
to system PATH for detect custom python module.