cmake_minimum_required(VERSION 3.27)
project(VirginiaCensus)

set(CMAKE_CXX_STANDARD 17)

add_executable( cartography main.cpp Color.cpp County.cpp )
