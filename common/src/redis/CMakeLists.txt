# redis组件的CMakeLists.txt

# 查找源文件
file(GLOB SOURCES "*.cpp" "*.cc")

# 创建库
if(SOURCES)
    add_library(redis ${SOURCES})
else()
    # 如果没有源文件，创建一个接口库
    add_library(redis INTERFACE)
endif()

# 设置头文件目录
target_include_directories(redis INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 安装
if(SOURCES)
    install(TARGETS redis DESTINATION lib)
endif()