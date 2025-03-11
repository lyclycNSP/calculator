cmake_minimum_required(VERSION 2.8)

project(calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall
    -Werror
    -pedantic
    -Wconversion
    -O3
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SOURCES
    ${SOURCE_DIR}/addition.cpp
    ${SOURCE_DIR}/calculation.cpp
    ${SOURCE_DIR}/calculator.cpp
    ${SOURCE_DIR}/division.cpp
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/multiplication.cpp
    ${SOURCE_DIR}/subtraction.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE ${INCULDE_DIR})

