cmake_minimum_required(VERSION 3.0)
project(socket)

#设置路径
set(CODE_SRC ${CMAKE_SOURCE_DIR}/src)
set(CODE_LIB ${CMAKE_SOURCE_DIR}/src_lib)
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

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})
find_library(LIBZIP_LIBRARY NAMES zip)


    file(GLOB CPP_SOURCE_FILES "${CODE_SRC}/*.cpp")

foreach(SOURCE_FILE ${CPP_SOURCE_FILES})
    # 获取文件名（不包含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    # 如果文件名不是 "Server_file.cpp" 且不是 "Client_file.cpp"，执行以下操作
    if(NOT (FILE_NAME STREQUAL "Server_file" OR FILE_NAME STREQUAL "Client_file"))
        # 生成可执行文件的名称
        set(EXECUTABLE_NAME "${FILE_NAME}")

        # 添加可执行文件
        add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
        # 如果特定的 CPP 文件需要链接特定的库，可以在这里添加链接关系
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE stdc++ ${ZLIB_LIBRARIES} ${LIBZIP_LIBRARY} archive)
    endif()
endforeach()


add_library(zip_library ${CODE_LIB}/zip2.cpp)
target_include_directories(zip_library PRIVATE ${CODE_INC})
target_link_libraries(zip_library PRIVATE stdc++ archive)
add_executable(Server_file ${CODE_SRC}/Server_file.cpp)
target_link_libraries(Server_file PRIVATE stdc++ zip_library)
target_include_directories(Server_file PRIVATE ${CODE_INC})

add_executable(Client_file ${CODE_SRC}/Client_file.cpp)
target_link_libraries(Client_file PRIVATE stdc++ zip_library)
target_include_directories(Client_file PRIVATE ${CODE_INC})