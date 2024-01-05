cmake_minimum_required(VERSION 3.17)
project(VACensus_Tests)

set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()

add_test( Test-1 "../cartography")
add_test( Test-2 "../cartography")
