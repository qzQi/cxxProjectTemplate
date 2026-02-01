# 为 gtest 测试创建可执行文件
add_executable(gtest_basic_test basic_test.cpp)

# 设置头文件路径
target_include_directories(gtest_basic_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/common/src/gtest
)

# 链接库文件 - 使用绝对路径
target_link_libraries(gtest_basic_test 
    ${CMAKE_SOURCE_DIR}/common/pkg/libgtest.a 
    ${CMAKE_SOURCE_DIR}/common/pkg/libgtest_main.a 
    pthread
)

# 设置输出目录
set_target_properties(gtest_basic_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)