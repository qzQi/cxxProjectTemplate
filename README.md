# C++ Development Framework

这是一个现代化的C++开发脚手架，把日常C++开发过程中常用的工具编译到本地，提供对应的头文件与库文件；  
最终通过Docker打包，构建一个可以开箱即用的C++开发环境；

## 特性

- **模块化设计**: 清晰的目录结构，便于扩展和维护
- **构建系统**: CMake + Shell脚本的自动化构建
- **依赖管理**: 依赖库集中管理
- **容器化**: Docker支持，开箱即用；

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
│   ├── tools/             # comom/pkg中必须的工具，比如protoc、grpc_cpp_plugin
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
TODO:

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
export LD_LIBRARY_PATH=/root/cxxProjectTemplate/common/pkg:$LD_LIBRARY_PATH
./pkg/main_app
```

### Docker部署
TODO

```bash
# 构建Docker镜像
docker build -t cxx-framework .

# 运行容器
docker run -it cxx-framework
```


## 依赖项

- CMake 3.10+
- GCC/G++ (支持C++17)

## 版本信息
- gRPC: 1.30.2
- Protobuf: 3.12.4
- protoc: 3.12.4
- gtest: 1.17.0


## 许可证

MIT License