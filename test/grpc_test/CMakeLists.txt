add_executable(grpc_server
    grpc_server.cpp
    proto/echo.pb.cc
    proto/echo.grpc.pb.cc
)

add_executable(grpc_client
    grpc_client.cpp
    proto/echo.pb.cc
    proto/echo.grpc.pb.cc
)

# 包含头文件
target_include_directories(grpc_server PRIVATE
    ${CMAKE_SOURCE_DIR}/common/src/
    ${CMAKE_SOURCE_DIR}/test/grpc_test/proto
)
target_include_directories(grpc_client PRIVATE
    ${CMAKE_SOURCE_DIR}/common/src/
    ${CMAKE_SOURCE_DIR}/test/grpc_test/proto
)

# 链接库
target_link_libraries(grpc_server PRIVATE
    ${CMAKE_SOURCE_DIR}/common/pkg/libgrpc++.so
    ${CMAKE_SOURCE_DIR}/common/pkg/libgrpc.so
    # ${CMAKE_SOURCE_DIR}/common/pkg/libgpr.so
    ${CMAKE_SOURCE_DIR}/common/pkg/libprotobuf.so
    pthread
)
target_link_libraries(grpc_client PRIVATE
    ${CMAKE_SOURCE_DIR}/common/pkg/libgrpc++.so
    ${CMAKE_SOURCE_DIR}/common/pkg/libgrpc.so
    # ${CMAKE_SOURCE_DIR}/common/pkg/libgpr.so
    ${CMAKE_SOURCE_DIR}/common/pkg/libprotobuf.so
    pthread
)
