cmake_minimum_required(VERSION 3.28)
project(k_core)

set(CMAKE_CXX_STANDARD 17)

add_executable(undirected_size_unbounded undirected_size_unbounded.cpp)
add_executable(directed_size_unbounded directed_size_unbounded.cpp)
