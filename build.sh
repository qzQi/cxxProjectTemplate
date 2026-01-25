#!/bin/bash

# 构建脚本
set -e  # 遇到错误时退出

# 默认为debug模式
BUILD_TYPE=${1:-Debug}
CLEAN_BUILD=${2:-false}

echo "Building in $BUILD_TYPE mode..."

# 创建构建目录
if [ "$CLEAN_BUILD" = "true" ]; then
    echo "Cleaning previous build..."
    rm -rf build/
fi

mkdir -p build
cd build

# 配置CMake
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# 编译
make -j$(nproc)

echo "Build completed successfully!"

# 如果有测试，运行测试
if [ -f ./test/unit_tests ]; then
    echo "Running unit tests..."
    ./test/unit_tests
elif [ -f test/unit_tests ]; then
    echo "Running unit tests..."
    ./test/unit_tests
fi

echo "All tasks completed!"