# protoc 工具路径
# $(CMAKE_SOURCE_DIR)/common/tools/grpc_cpp_plugin
# $(CMAKE_SOURCE_DIR)/common/tools/protoc
PROJECT_ROOT := ../../..
PROTOC = $(PROJECT_ROOT)/common/tools/protoc
GRPC_PLUGIN = $(PROJECT_ROOT)/common/tools/grpc_cpp_plugin  # grpc 插件

# 当前目录下所有 proto 文件
PROTO_FILES := $(wildcard *.proto)

# 生成的 protobuf C++ 文件
GEN_SRCS := $(PROTO_FILES:%.proto=%.pb.cc)
GEN_HDRS := $(PROTO_FILES:%.proto=%.pb.h)

# 生成的 gRPC C++ 文件
GEN_GRPC_SRCS := $(PROTO_FILES:%.proto=%.grpc.pb.cc)
GEN_GRPC_HDRS := $(PROTO_FILES:%.proto=%.grpc.pb.h)

# 默认目标：生成所有 pb + grpc.pb 文件
all: $(GEN_SRCS) $(GEN_HDRS) $(GEN_GRPC_SRCS) $(GEN_GRPC_HDRS)

# ================= 核心规则 =================
# protobuf 普通文件生成
%.pb.cc %.pb.h: %.proto
	@echo "Generating protobuf $@ from $<"
	$(PROTOC) --cpp_out=. $<

# grpc 文件生成
%.grpc.pb.cc %.grpc.pb.h: %.proto
	@echo "Generating gRPC $@ from $<"
	$(PROTOC) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_PLUGIN) $<

# 清理
clean:
	rm -f *.pb.cc *.pb.h *.grpc.pb.cc *.grpc.pb.h

.PHONY: all clean
