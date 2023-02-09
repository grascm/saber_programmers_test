cmake_minimum_required(VERSION 3.24)
project(saber_programmers_test)
set(CMAKE_CXX_STANDARD 20)

# num_to_bits application

SET(NUM_TO_BITS_SOURCES
        src/num_to_bits.cpp)

add_executable(num_to_bits ${NUM_TO_BITS_SOURCES})
target_compile_options(num_to_bits PRIVATE -Wall -Wextra -Wpedantic -Werror)

# remove_dups application

SET(REMOVE_DUPS_SOURCES
        src/remove_dups.cpp)

add_executable(remove_dups ${REMOVE_DUPS_SOURCES})
target_compile_options(remove_dups PRIVATE -Wall -Wextra -Wpedantic -Werror)

# serializer application

SET(SERIALIZER_SOURCES
        src/serializer.cpp)

add_executable(serializer ${SERIALIZER_SOURCES})
target_compile_options(serializer PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Unit tests

enable_testing()
find_package(GTest REQUIRED)

SET(TEST_SOURCES
        tests/t_num_to_bits.cpp
        tests/t_remove_dups.cpp
        tests/t_serializer.cpp)

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

add_test(NAME unit_test COMMAND tests)