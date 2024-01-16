cmake_minimum_required(VERSION 3.17)
project(VACensus_Tests)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

include(CTest)
enable_testing()

add_executable( test Test_DBConnection.cpp)
add_executable( test2 Test_DBConnection_Fail.cpp)

add_test( Connection_Test test )
add_test( Connection_Test_Fail test2 )
set_tests_properties( Connection_Test_Fail PROPERTIES WILL_FAIL TRUE )

# Link to the name of the EXECUTABLE, not the project
target_link_libraries(test PostgreSQL::PostgreSQL)
target_link_libraries(test2 PostgreSQL::PostgreSQL)