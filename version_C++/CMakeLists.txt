cmake_minimum_required(VERSION 3.27)
project(VirginiaCensus)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

add_subdirectory(Tests)
add_executable( cartography main.cpp Color.cpp County.cpp )

# Link to the name of the EXECUTABLE, not the project
target_link_libraries(cartography PostgreSQL::PostgreSQL)
