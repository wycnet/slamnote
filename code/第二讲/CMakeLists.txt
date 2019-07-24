# 申明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 声明一个cmake工程
project(HelloSLAM)

# 添加一个可执行程序
# 语法: add_executable(程序名 源代码文件)
add_executable(useHello useHello.cpp)
add_library(hello_shared SHARED libHelloSLAM.cpp)

target_link_libraries(useHello hello_shared)

