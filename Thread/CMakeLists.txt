cmake_minimum_required(VERSION 3.0)
project(thread)

#设置路径
set(CODE_SRC ${CMAKE_SOURCE_DIR}/src)
set(CODE_INC ${CMAKE_SOURCE_DIR}/inc)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")    #可执行文件路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")    #*.so *.dll
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")       #*.a

add_library(demo_03_library ${CODE_SRC}/demo_03.cpp)                #编译成demo_03_library库
target_link_libraries(demo_03_library PRIVATE  pthread)             #添加线程库
target_include_directories(demo_03_library PRIVATE  ${CODE_INC})    #添加头文件
add_executable(ergodic_old ${CODE_SRC}/ergodic_old.c )              #生成ergodic_old可执行文件
target_link_libraries(ergodic_old PRIVATE  demo_03_library rocksdb) #添加各种库
target_include_directories(ergodic_old PRIVATE  ${CODE_INC})        #添加头文件