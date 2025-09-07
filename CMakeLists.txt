cmake_minimum_required(VERSION 3.10)

project(main C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.cc")

add_executable(main ${SOURCES})

target_compile_options(main PRIVATE -mwindows)
target_link_libraries(main PRIVATE SDL3 SDL3_ttf)