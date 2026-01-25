# memory_pool组件的CMakeLists.txt

# 查找源文件
file(GLOB SOURCES "*.cpp" "*.cc")

# 创建库
if(SOURCES)
    add_library(memory_pool ${SOURCES})
else()
    # 如果没有源文件，创建一个接口库
    add_library(memory_pool INTERFACE)
endif()

# 预编译库链接tcmalloc
# 检查tcmalloc库是否存在
find_library(TCMALLOC_LIB tcmalloc PATHS ${PROJECT_SOURCE_DIR}/common/pkg NO_DEFAULT_PATH)

if(TCMALLOC_LIB)
    message(STATUS "Found tcmalloc: ${TCMALLOC_LIB}")
    if(SOURCES)
        target_compile_definitions(memory_pool PRIVATE USE_TCMALLOC)
        target_link_libraries(memory_pool ${TCMALLOC_LIB})
    else()
        target_compile_definitions(memory_pool INTERFACE USE_TCMALLOC)
        target_link_libraries(memory_pool INTERFACE ${TCMALLOC_LIB})
    endif()
else()
    message(WARNING "tcmalloc not found in common/pkg, using system allocator")
endif()

# 设置头文件目录
target_include_directories(memory_pool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 安装
if(SOURCES)
    install(TARGETS memory_pool DESTINATION lib)
endif()