include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../src)
set(AccountSystemFixtures  AccountSystemFixture ../src/AccountSystem ../src/Account AccountFixture.cpp
        DrawCardSystemFixture.cpp ../src/DrawCardSystem.cpp
        ../src/CardInfoSystem.cpp CardInfoSystemFixture.cpp )
add_executable(FunctionalTest test_main.cpp ${AccountSystemFixtures} )
target_link_libraries(FunctionalTest  gtest gtest_main)