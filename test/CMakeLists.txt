# 包含子目录
add_subdirectory(gtest_test)

# 添加protobuf测试子目录
add_subdirectory(protobuf_test)

add_subdirectory(grpc_test)

# 如果需要其他测试目录，可以继续添加
# add_subdirectory(brpc_test)
# add_subdirectory(grpc_test)