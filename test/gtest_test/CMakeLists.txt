add_executable(gtest_basic_test basic_test.cpp)

# 头文件路径
target_include_directories(gtest_basic_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/common/src/gtest
)

# 链接库
target_link_libraries(gtest_basic_test PRIVATE
    ${CMAKE_SOURCE_DIR}/common/pkg/libgtest.a
    ${CMAKE_SOURCE_DIR}/common/pkg/libgtest_main.a
    pthread
)
