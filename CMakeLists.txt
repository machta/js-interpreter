cmake_minimum_required(VERSION 3.1)
project(js-interpreter)

# Options.
set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS off CACHE BOOL "")

# First build all the library dependencies.
#add_subdirectory(jast)
file(GLOB JAST_SRC jast/src/jast/*)
include_directories(jast/include)

# The library.
include_directories(src)
file(GLOB SRC src/*.cpp src/*.h)
list(REMOVE_ITEM SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_library(js-interpreter-lib ${SRC} ${JAST_SRC})

# The exe.
add_executable(js-interpreter src/main.cpp)
target_link_libraries(js-interpreter js-interpreter-lib)

if(MSVC)
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "-W4")
else()
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "-Wall -pedantic")# -Wextra -Wconversion")
endif()

add_subdirectory(unit-test)
