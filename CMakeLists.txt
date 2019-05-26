cmake_minimum_required(VERSION 3.13)

project(Another-Card-Game-ACG)
set(CMAKE_CXX_STANDARD 17)
set(DO_TEST FALSE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pthread -std=c++17 -Wall")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GNU
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread") # for using std::thread in gcc
endif()

include_directories(lib)
include_directories(src)
include_directories(src/pages)


add_subdirectory(src)

if (DO_TEST)
    add_subdirectory(lib/googletest-master)
    include_directories(lib/googletest-master/googletest/include)
    include_directories(lib/googletest-master/googlemock/include)
    add_subdirectory(test)
    include_directories("test")
    set(TEST_FILES "test_main.cpp")
    add_executable(test_main test/test_main.cpp)
    target_link_libraries(test_main gtest gtest_main)
endif(DO_TEST)



file(COPY data DESTINATION .)
file(COPY test/data DESTINATION test)
file(COPY test/data/accountlist.json DESTINATION test/accountlist.json)
file(COPY test/data/cardlist.json DESTINATION test/xardlist.json)

add_executable(main main.cpp)
target_link_libraries(main ACGMain AccountSystem Room GameSystem ACGIO)