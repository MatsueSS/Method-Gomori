cmake_minimum_required(VERSION 3.10)

project(gomori)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/good_funcs.cpp
    src/prepare_simplex.cpp
    src/simplex_method
    src/generator_zlp.cpp
    src/gomori.cpp
    src/mvag.c
)