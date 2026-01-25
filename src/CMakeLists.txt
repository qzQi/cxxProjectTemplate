# src目录的CMakeLists.txt

# 查找所有源文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.cc" "*.c")

# 如果找到源文件，则创建可执行文件
if(SOURCES)
    # 获取目录名作为目标名
    get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    
    # 创建可执行文件
    add_executable(main_app ${SOURCES})
    
    # 链接common库
    target_link_libraries(main_app common)
    
    # 设置输出目录
    set_target_properties(main_app PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/pkg
    )
endif()