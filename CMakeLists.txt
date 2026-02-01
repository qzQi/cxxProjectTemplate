cmake_minimum_required(VERSION 3.10)
project(cxx_project_temp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

# Debug/Release编译选项
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# 预编译库管理
# 添加common/pkg到库搜索路径
link_directories(${PROJECT_SOURCE_DIR}/common/pkg)

# 添加common/src到头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/common/src)

# 直接链接预编译的tcmalloc库（如果存在）
# 如果common/pkg目录下有libtcmalloc.a或libtcmalloc.so，则直接链接
# link_libraries(tcmalloc)  # 根据实际库文件名调整

# 包含common库
add_subdirectory(common)

# 包含业务代码
add_subdirectory(src)

# 测试代码
add_subdirectory(test)