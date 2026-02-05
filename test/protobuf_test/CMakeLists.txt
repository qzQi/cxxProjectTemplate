add_executable(protobuf_test protobuf_test.cpp proto/test.pb.cc)

# 头文件路径
target_include_directories(protobuf_test PRIVATE
    ${CMAKE_SOURCE_DIR}/proto
    ${CMAKE_SOURCE_DIR}/common/src/google
)

# 链接 protobuf 库
target_link_libraries(protobuf_test PRIVATE
    ${CMAKE_SOURCE_DIR}/common/pkg/libprotobuf.a
)
