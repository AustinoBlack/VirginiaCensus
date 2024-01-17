cmake_minimum_required(VERSION 3.17)
project(VACensus_Tests)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

include(CTest)
enable_testing()

add_executable( compare file_comparor.cpp )
add_executable( conn Test_DBConnection.cpp)
add_executable( connf Test_DBConnection_Fail.cpp)
add_executable( query Test_DBQuery.cpp )
add_executable( queryf Test_DBQuery_Fail.cpp )

add_test( Connection_Test conn )
add_test( Connection_Test_Fail connf )
add_test( Query_Execution_Test query)
add_test( Query_Execution_Test_Fail queryf)
add_test( compare_files_test compare "one.txt" "two.txt")
add_test( compare_files_test_Fail compare "one.txt" "wrong.txt")


# Test Fail Exceptions
set_tests_properties( Connection_Test_Fail PROPERTIES WILL_FAIL TRUE )
set_tests_properties( Query_Execution_Test_Fail PROPERTIES WILL_FAIL TRUE )
set_tests_properties( compare_files_test_Fail PROPERTIES WILL_FAIL TRUE )

# Link to the name of the EXECUTABLE, not the project
target_link_libraries(conn PostgreSQL::PostgreSQL)
target_link_libraries(connf PostgreSQL::PostgreSQL)
target_link_libraries(query PostgreSQL::PostgreSQL)
target_link_libraries(queryf PostgreSQL::PostgreSQL)