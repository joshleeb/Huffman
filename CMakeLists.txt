cmake_minimum_required(VERSION 3.0)
project(huffman)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Werror")

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cc src/*.h)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS filesystem program_options)

add_executable(huffman src/main.cc ${LIBS} ${SOURCES})

target_link_libraries(huffman ${Boost_LIBRARIES})

find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes $<TARGET_FILE:huffman>)
endif()
