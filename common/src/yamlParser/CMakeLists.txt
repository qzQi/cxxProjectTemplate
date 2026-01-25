# yamlParser组件的CMakeLists.txt

# 查找源文件
file(GLOB SOURCES "*.cpp" "*.cc")

# 创建库
if(SOURCES)
    add_library(yaml_parser ${SOURCES})
else()
    # 如果没有源文件，创建一个接口库
    add_library(yaml_parser INTERFACE)
endif()

# 设置头文件目录
target_include_directories(yaml_parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有实现文件，设置输出目录到上级pkg目录
if(SOURCES)
    set_target_properties(yaml_parser PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../pkg
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../pkg
    )
endif()

# 安装
if(SOURCES)
    install(TARGETS yaml_parser DESTINATION lib)
endif()