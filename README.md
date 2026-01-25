# C++ Development Framework

这是一个现代化的C++开发脚手架，旨在为后续的网络库和RPC框架开发提供坚实的基础。

## 特性

- **模块化设计**: 清晰的目录结构，便于扩展和维护
- **日志系统**: 集成高性能日志系统
- **异常处理**: 统一的异常处理机制
- **内存管理**: 支持tcmalloc等高效内存管理器
- **构建系统**: CMake + Shell脚本的自动化构建
- **测试框架**: 集成Google Test单元测试框架
- **容器化**: Docker支持，便于部署和分发

## 目录结构

```
cxxProjextTemp/
├── common/                 # 公共依赖库
│   ├── src/               # 封装的操作库
│   │   ├── redis/         # Redis连接池和操作封装
│   │   ├── mongo/         # MongoDB连接和操作封装  
│   │   ├── time_scheduler/# 定时任务调度器
│   │   ├── yamlParser/    # YAML配置文件解析器
│   │   ├── threadPool/    # 线程池管理器
│   │   ├── logger/        # 日志系统
│   │   ├── exception/     # 异常处理
│   │   └── memory_pool/   # 内存池管理(tcmalloc)
│   ├── pkg/               # 第三方依赖库
│   └── CMakeLists.txt     # common库构建配置
├── pkg/                   # 编译后的可执行文件输出目录
├── src/                   # 业务代码目录
│   └── CMakeLists.txt     # src模块构建配置
├── test/                  # 单元测试目录
│   └── CMakeLists.txt     # 测试构建配置
├── build.sh              # 构建脚本
├── CMakeLists.txt        # 顶层CMake配置
└── Dockerfile            # 容器化部署文件
```

## 快速开始

### 构建项目

```bash
# 构建Debug版本
./build.sh Debug

# 构建Release版本
./build.sh Release

# 清理后重新构建
./build.sh Debug true
```

### 运行应用

```bash
# 运行生成的可执行文件
./pkg/main_app
```

### Docker部署

```bash
# 构建Docker镜像
docker build -t cxx-framework .

# 运行容器
docker run -it cxx-framework
```

## 后续项目

此脚手架将为以下项目提供支撑：
1. Reactor网络库(muduo风格)
2. RPC框架(集成protobuf和网络层)

## 依赖项

- CMake 3.10+
- GCC/G++ (支持C++17)
- spdlog (可选，用于高级日志功能)
- Google Test (用于单元测试)
- tcmalloc (可选，用于高效内存管理)

## 组件说明

### Logger
轻量级日志系统，支持多种输出格式和级别。

### Exception
统一的异常处理体系，包含各种特定异常类型。

### Memory Pool
集成了tcmalloc等高效内存管理器的封装。

## 许可证

MIT License