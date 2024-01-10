cmake_minimum_required(VERSION 3.0)
project(socket)

#设置路径
set(CODE_SRC ${CMAKE_SOURCE_DIR}/src)
set(CODE_INC ${CMAKE_SOURCE_DIR}/inc)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")    #可执行文件路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")    #*.so *.dll
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")       #*.a

include_directories(${CODE_INC}) 
# 获取源文件列表
file(GLOB SOURCE_FILES "${CODE_SRC}/*.c")
# 遍历源文件列表生成可执行文件
foreach(SOURCE_FILE ${SOURCE_FILES})
    # 获取文件名（不包含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)

    # 生成可执行文件的名称
    set(EXECUTABLE_NAME "${FILE_NAME}")

    # 添加可执行文件
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
endforeach()

file(GLOB CPP_SOURCE_FILES "${CODE_SRC}/*.cpp")
foreach(SOURCE_FILE ${CPP_SOURCE_FILES})
    # 获取文件名（不包含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)

    # 生成可执行文件的名称
    set(EXECUTABLE_NAME "${FILE_NAME}")

    # 添加可执行文件
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    # 如果特定的 CPP 文件需要链接特定的库，可以在这里添加链接关系
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE stdc++)

endforeach()