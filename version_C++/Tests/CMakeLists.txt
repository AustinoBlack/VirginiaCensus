cmake_minimum_required(VERSION 3.17)
project(VACensus_Tests)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

include(CTest)
enable_testing()

# list of counties - for tests
set( COUNTIES
        Accomack
        Albemarle
        Alleghany
        Amelia
        Amherst
        Appomattox
        Arlington
        Augusta
        Bath
        Bedford
        Bland
        Botetourt
        Brunswick
        Buchanan
        Buckingham
        Campbell
        Caroline
        Carroll
        Charles_City
        Charlotte
        Chesterfield
        Clarke
        Craig
        Culpeper
        Cumberland
        Dickenson
        Dinwiddie
        Essex
        Fairfax
        Fauquier
        Floyd
        Fluvanna
        Franklin
        Frederick
        Giles
        Gloucester
        Goochland
        Grayson
        Greene
        Greensville
        Halifax
        Hanover
        Henrico
        Henry
        Highland
        Isle_of_Wight
        James_City
        King_and_Queen
        King_George
        King_William
        Lancaster
        Lee
        Loudoun
        Louisa
        Lunenburg
        Madison
        Mathews
        Mecklenburg
        Middlesex
        Montgomery
        Nelson
        New_Kent
        Northampton
        Northumberland
        Nottoway
        Orange
        Page
        Patrick
        Pittsylvania
        Powhatan
        Prince_Edward
        Prince_George
        Prince_William
        Pulaski
        Rappahannock
        Richmond
        Roanoke
        Rockbridge
        Rockingham
        Russell
        Scott
        Shenandoah
        Smyth
        Southampton
        Spotsylvania
        Stafford
        Surry
        Sussex
        Tazewell
        Warren
        Washington
        Westmoreland
        Wise
        Wythe
        York
        Alexandria.City
        Bristol.City
        Buena_Vista.City
        Charlottesville.City
        Chesapeake.City
        Colonial_Heights.City
        Covington.City
        Danville.City
        Emporia.City
        Fairfax.City
        Falls_Church.City
        Franklin.City
        Fredericksburg.City
        Galax.City
        Hampton.City
        Harrisonburg.City
        Hopewell.City
        Lexington.City
        Lynchburg.City
        Manassas.City
        Manassas_Park.City
        Martinsville.City
        Newport_News.City
        Norfolk.City
        Norton.City
        Petersburg.City
        Poquoson.City
        Portsmouth.City
        Radford.City
        Richmond.City
        Roanoke.City
        Salem.City
        Staunton.City
        Suffolk.City
        Virginia_Beach.City
        Waynesboro.City
        Williamsburg.City
        Winchester.City
)

# compile files
add_executable( compare file_comparor.cpp )
add_executable( Test_Color Test_Create_Color.cpp "../Color.cpp" )
add_executable( conn Test_DBConnection.cpp)
add_executable( connf Test_DBConnection_Fail.cpp)
add_executable( query Test_DBQuery.cpp )
add_executable( queryf Test_DBQuery_Fail.cpp )

# DB connection tests
add_test( Connection_Test conn )
add_test( Connection_Test_Fail connf )

# Query Execution tests
add_test( Query_Execution_Test query )
add_test( Query_Execution_Test_Fail queryf )

# File Comparor tests
add_test( compare_files_test_Fail compare "Wrong.txt" "Color_Output.txt" )
add_test( compare_files_bad_cmd compare "Correct.txt" )
add_test( compare_files_bad_cmd_2 compare )
add_test( compare_files_bad_cmd_3 compare "Wrong.txt" )

# Run Test_Color exec for each county
foreach ( COUNTY IN LISTS COUNTIES)
    add_test( Run_${COUNTY} Test_Color ${COUNTY})
endforeach ()

# Created <path> tag tests for each county
foreach ( COUNTY IN LISTS COUNTIES)
    add_test( Compare_${COUNTY} compare ${COUNTY}.txt ${COUNTY}.txt)
endforeach ()

# Test Fail Exceptions
set_tests_properties( Connection_Test_Fail PROPERTIES WILL_FAIL TRUE )
set_tests_properties( Query_Execution_Test_Fail PROPERTIES WILL_FAIL TRUE )
set_tests_properties( compare_files_test_Fail PROPERTIES WILL_FAIL TRUE )
set_tests_properties( compare_files_bad_cmd PROPERTIES WILL_FAIL TRUE )
set_tests_properties( compare_files_bad_cmd_2 PROPERTIES WILL_FAIL TRUE )
set_tests_properties( compare_files_bad_cmd_3 PROPERTIES WILL_FAIL TRUE )

# Link to the name of the EXECUTABLE, not the project
target_link_libraries(conn PostgreSQL::PostgreSQL)
target_link_libraries(connf PostgreSQL::PostgreSQL)
target_link_libraries(query PostgreSQL::PostgreSQL)
target_link_libraries(queryf PostgreSQL::PostgreSQL)
target_link_libraries(Test_Color PostgreSQL::PostgreSQL)