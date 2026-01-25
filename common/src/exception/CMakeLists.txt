# exception组件的CMakeLists.txt

# 查找源文件
file(GLOB SOURCES "*.cpp" "*.cc")

# 创建库
if(SOURCES)
    add_library(exception ${SOURCES})
else()
    # 如果没有源文件，创建一个接口库
    add_library(exception INTERFACE)
endif()

# 设置头文件目录
target_include_directories(exception INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 安装
if(SOURCES)
    install(TARGETS exception DESTINATION lib)
endif()