cmake_minimum_required( VERSION 2.8 )

project( ceres_curve_fitting )

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

#添加cmake模块以使用ceres库
#list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# 寻找ceres库并添加它的头文件
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# OpenCV
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_DIRS})

add_executable(curve_fitting ceresLine.cpp)

target_link_libraries(curve_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS}  )