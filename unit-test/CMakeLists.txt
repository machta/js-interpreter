# Build Google Test library.
set(BUILD_GMOCK OFF)
set(BUILD_GTEST ON)
add_subdirectory(googletest)
include_directories(../include googletest/googletest/include)

# The tests.
file(GLOB SRC *.cpp)
add_executable(unit-test ${SRC})
target_link_libraries(unit-test js-interpreter-lib gtest gtest_main)
