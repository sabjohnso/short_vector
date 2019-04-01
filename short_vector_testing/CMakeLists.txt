include(FetchGTest)

add_executable(short_vector_auto_test short_vector_auto_test.cpp)
target_link_libraries(short_vector_auto_test PRIVATE gtest_main short_vector::short_vector)
set_target_properties(short_vector_auto_test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
add_test(short_vector_auto short_vector_auto_test)



add_executable(m256_test m256_test.cpp)
target_link_libraries(m256_test PRIVATE gtest_main short_vector::short_vector)
set_target_properties(m256_test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED TRUE)
add_test(m256 m256_test)
