cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(03_CppStandards)

file(GLOB SOURCES "*.cpp")

add_executable(03_CppStandards ${SOURCES})

target_include_directories(03_CppStandards PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(03_CppStandards PRIVATE /W4)
else()
    target_compile_options(03_CppStandards PRIVATE
        -Wall
        -Wextra
        -Wpedantic)
endif()