FROM ubuntu:20.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive

# 更新包列表并安装必要的构建工具
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    vim \
    pkg-config \
    libtcmalloc-dev \
    && rm -rf /var/lib/apt/lists/*

# 安装Google Test
RUN git clone https://github.com/google/googletest.git && \
    cd googletest && \
    mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    cd ../.. && \
    rm -rf googletest

# 设置工作目录
WORKDIR /app

# 复制项目文件
COPY . .

# 创建pkg目录
RUN mkdir -p pkg

# 构建项目
RUN chmod +x build.sh && \
    ./build.sh Release

# 默认命令
CMD ["bash"]