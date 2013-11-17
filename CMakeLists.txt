cmake_minimum_required (VERSION 2.6)
project (esh-cpp)

add_executable(esh list.cpp)#esh.c builtins.c format.c gc.c hash.c list.c)

set( CMAKE_CXX_FLAGS " --std=c++0x -O2 -g -Wall")
