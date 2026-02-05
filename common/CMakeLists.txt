# common库的CMakeLists.txt

# 设置库输出目录
set(COMMON_LIBRARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pkg)
file(MAKE_DIRECTORY ${COMMON_LIBRARY_OUTPUT_DIR})

# 设置CMAKE_PREFIX_PATH，以便find_package能找到pkg中的库
list(APPEND CMAKE_PREFIX_PATH ${COMMON_LIBRARY_OUTPUT_DIR})

# 设置库搜索路径
link_directories(${COMMON_LIBRARY_OUTPUT_DIR})

# 添加各个组件子目录
add_subdirectory(src/redis)
add_subdirectory(src/mongo)
add_subdirectory(src/yamlParser)
add_subdirectory(src/threadPool)
add_subdirectory(src/logger)
add_subdirectory(src/exception)
add_subdirectory(src/memory_pool)


# 创建一个别名，让其他模块可以通过common访问所有组件
add_library(common INTERFACE)

# 链接到各个组件库
target_link_libraries(common
    INTERFACE
        logger
        yaml_parser
        exception
        memory_pool
)


target_include_directories(common
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/redis
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mongo
        ${CMAKE_CURRENT_SOURCE_DIR}/src/yamlParser
        ${CMAKE_CURRENT_SOURCE_DIR}/src/threadPool
        ${CMAKE_CURRENT_SOURCE_DIR}/src/logger
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception
        ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_pool
        ${COMMON_LIBRARY_OUTPUT_DIR}
)