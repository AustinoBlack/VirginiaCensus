cmake_minimum_required(VERSION 3.27)
project(VirginiaCensus)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

add_subdirectory(Tests)
add_executable( cartography main.cpp Color.cpp County.cpp )

target_link_libraries(VirginiaCensus PostgreSQL::PostgreSQL)
