cmake_minimum_required(VERSION 3.10)

project(main C CXX)

# include_directories(${CMAKE_SOURCE_DIR}/include)

# 定义一个宏来递归查找所有包含 .h 文件的目录
MACRO(GET_HEADER_DIRECTORIES return_list)
    file(GLOB_RECURSE new_list ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h) # 递归查找所有 .h 文件
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        get_filename_component(dir_path ${file_path} DIRECTORY) # 提取每个头文件所在的目录
        LIST(APPEND dir_list ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list) # 移除重复的目录
    SET(${return_list} ${dir_list}) # 将结果列表赋值给传入的变量
ENDMACRO()

# 调用宏，获取所有头文件目录
GET_HEADER_DIRECTORIES(HEADER_DIRS)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*/*.cpp" "${CMAKE_SOURCE_DIR}/src/*/*.cc")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.cc")

add_executable(main ${SOURCES})

target_compile_options(main PRIVATE -mwindows)
target_link_libraries(main PRIVATE SDL3 SDL3_ttf)

target_include_directories(main PUBLIC ${HEADER_DIRS})