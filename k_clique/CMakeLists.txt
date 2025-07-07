cmake_minimum_required(VERSION 3.28)
project(k_clique)

set(CMAKE_CXX_STANDARD 17)

add_executable(ocs ocs.cpp)
add_executable(dcpc DCPC.cpp)
