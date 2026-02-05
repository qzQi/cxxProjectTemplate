cmake_minimum_required(VERSION 3.10)
project(cxx_project_temp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# 全局头文件路径
include_directories(${PROJECT_SOURCE_DIR}/common/src)

# 全局库路径
link_directories(${PROJECT_SOURCE_DIR}/common/pkg)

# 统一管理所有可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 子目录
add_subdirectory(common)
add_subdirectory(src)
add_subdirectory(test)
