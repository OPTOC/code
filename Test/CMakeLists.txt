cmake_minimum_required(VERSION 3.0)
project(main)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CODE_SRC ${CMAKE_SOURCE_DIR}/code/src)
set(CODE_INC ${CMAKE_SOURCE_DIR}/code/inc)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#设置main的下载地址 //CMake.txt文件所在位置CMAKE_SOURCE_DIR 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")#可执行文件
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")#*.so *.dll
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")#*.a
set(IFCONFIG 1)#选择链接模式

if(${IFCONFIG})
##链接方式一
add_executable(main ${CODE_SRC}/main.c ${CODE_SRC}/pr.c)
include_directories(${CODE_INC}) #指定头文件目录
message("这是方式一")
else()
##链接方式二
add_library(main_library ${CODE_SRC}/pr.c)
add_executable(main ${CODE_SRC}/main.c)
target_link_libraries(main ${CODE_SRC}/main_library)
include_directories(${CODE_INC}) #指定头文件目录
message("这是方式二")
endif()
# 如果 pr.c 和 pr.h 在不同的目录，你可以使用 include_directories 命令
# include_directories(path/to/pr/header)

##g++ -o your_program_name your_program_name.cpp -lrocksdb
#这是编译demo_01的
set(SOURCE_FILES_01 ${CODE_SRC}/demo_01.cpp)
# 添加可执行文件 01
add_executable(demo_01 ${SOURCE_FILES_01})
target_link_libraries(demo_01 PRIVATE rocksdb)

##gcc -Wall passthrough_fh.c `pkg-config fuse3 --cflags --libs` -o xmp
#编译fuse   #其实可以和上面demo_01类似只不过这种比较详细
# 添加 FUSE 依赖
find_package(PkgConfig REQUIRED)
#如果 REQUIRED 被设置为 REQUIRED，并且 CMake 无法找到指定的包，
#那么 find_package 将导致构建过程失败，并产生一个错误消息。
pkg_search_module(FUSE3 REQUIRED ${CODE_SRC}/fuse3)
# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
# 添加可执行文件
add_executable(xmp ${CODE_SRC}/passthrough_fh.c)
# 链接 FUSE 库
target_link_libraries(xmp PRIVATE ${FUSE3_LIBRARIES})
# 添加 FUSE 头文件路径
target_include_directories(xmp PRIVATE ${FUSE3_INCLUDE_DIRS})


##混编demo与fuse
 find_package(PkgConfig REQUIRED)
 pkg_search_module(FUSE3 REQUIRED fuse3)#在pkgconfig里面找到fuse3并且改为FUSE3
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
 
 add_library(main_library ${CODE_SRC}/demo_02.cpp)
 add_executable(fuse_test ${CODE_SRC}/fuse_test.c)
 target_link_libraries(fuse_test PRIVATE main_library ${FUSE3_LIBRARIES} rocksdb)
 target_include_directories(fuse_test PRIVATE ${FUSE3_INCLUDE_DIRS})

#  set_target_properties(fuse_test PROPERTIES
#         ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#         LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )