# logger组件的CMakeLists.txt

# 查找源文件
file(GLOB SOURCES "*.cpp" "*.cc")

# 简单的logger库实现，不需要外部依赖
# 注意：我们不再使用${SOURCES}变量，而是直接指定源文件
add_library(logger logger.cpp)

# 设置头文件目录
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 设置输出目录到上级pkg目录
set_target_properties(logger PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../pkg
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../pkg
)

# 安装
install(TARGETS logger DESTINATION lib)