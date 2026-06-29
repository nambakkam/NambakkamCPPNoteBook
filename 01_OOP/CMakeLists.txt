cmake_minimum_required(VERSION 3.16)

project(01_OOP)

file(GLOB SOURCES "*.cpp")

add_executable(01_OOP ${SOURCES})

target_include_directories(01_OOP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(01_OOP PRIVATE /W4)
else()
    target_compile_options(01_OOP PRIVATE
        -Wall
        -Wextra
        -Wpedantic)
endif()