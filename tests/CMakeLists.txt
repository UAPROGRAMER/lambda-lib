cmake_minimum_required(VERSION 3.16)
project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/dest/"
)

file(GLOB sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

include_directories("../src")

foreach(source IN ITEMS ${sources})
    get_filename_component(source_name "${source}" NAME_WE)
    add_executable(${source_name} ${source})
endforeach()
