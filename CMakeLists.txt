cmake_minimum_required (VERSION 2.6)
project (esh-cpp)
find_package( Boost )	
if(NOT Boost_FOUND)
	message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
endif()

include_directories(${Boost_INCLUDE_DIRS})
add_executable(esh list.cpp)#esh.c builtins.c format.c gc.c hash.c list.c)
#target_link_libraries(esh ${Boost_FILESYSTEM_LIBRARY}})
set( CMAKE_CXX_FLAGS " --std=c++0x -O2 -g -Wall")

