PROTOC = protoc

# 当前目录下所有 proto 文件
PROTO_FILES := $(wildcard *.proto)

# 由 proto 推导出的目标文件（就在当前目录）
GEN_SRCS := $(PROTO_FILES:%.proto=%.pb.cc)
GEN_HDRS := $(PROTO_FILES:%.proto=%.pb.h)

# 默认目标
all: $(GEN_SRCS) $(GEN_HDRS)

# 核心规则：proto -> pb.cc + pb.h（就在当前目录）
%.pb.cc %.pb.h: %.proto
	@echo "Generating $@ from $<"
	$(PROTOC) --cpp_out=. $<

# 清理当前目录生成的 pb 文件
clean:
	rm -f *.pb.cc *.pb.h

.PHONY: all clean