# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
# Default: Build in Debug mode
./build.sh

# Build in Release mode
./build.sh Release

# Clean build (removes build/ directory first)
./build.sh Debug true
./build.sh Release true
```

The build script automatically runs tests after compilation if `build/test/unit_tests` exists.

Build outputs:
- Main application: `pkg/main_app`
- Test executables: `build/test/`

## Code Architecture

This is a C++17 development scaffold with a modular design. The codebase is organized into three main sections:

### Common Library (`common/`)

Reusable components and third-party dependencies. The `common` library is an INTERFACE library that aggregates all modules.

**Key Components:**
- `logger/` - Logging system with debug/info/warn/error levels
- `exception/` - Hierarchical exception classes (BaseException, ConfigException, NetworkException, DatabaseException, MemoryException)
- `memory_pool/` - Wraps tcmalloc or standard malloc/free (controlled by `USE_TCMALLOC` macro)
- `yamlParser/` - YAML configuration parser
- `threadPool/` - Thread pool manager
- `time_scheduler/` - Task scheduler
- `redis/` - Redis client with connection pooling
- `mongo/` - MongoDB client interface
- `google/protobuf/` - Protocol Buffers implementation
- `gtest/` - Google Test framework (precompiled in `common/pkg/`)

### Application (`src/`)

The `src/CMakeLists.txt` automatically creates a single executable `main_app` from all `*.cpp`, `*.cc`, `*.c` files found recursively. The executable links against `common` and outputs to `pkg/`.

### Tests (`test/`)

Organized by testing framework:
- `test/gtest_test/` - Google Test unit tests
- `test/protobuf_test/` - Protocol Buffer tests
- `test/grpc_test/` - gRPC tests (not yet added to build)

Individual test execution:
```bash
cd build
./test/gtest_basic_test
```

## Adding a New Module to Common Library

1. Create directory in `common/src/[module_name]/`
2. Create `common/src/[module_name]/CMakeLists.txt`:
   ```cmake
   file(GLOB SOURCES "*.cpp" "*.cc")
   add_library(module_name ${SOURCES})
   target_include_directories(module_name INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
   ```
3. Add to `common/CMakeLists.txt`:
   ```cmake
   add_subdirectory(src/[module_name])
   # Add to target_link_libraries if linking is needed
   # Add include path to target_include_directories(common INTERFACE ...)
   ```

## Third-Party Dependencies

- Static libraries go in `common/pkg/`
- Tools (like `protoc`, `grpc_cpp_plugin`) go in `common/tools/`
- VS Code is configured to find protoc at `common/tools/protoc` (see `.vscode/settings.json`)

## Compiler Flags

- Standard: C++17
- Common: `-Wall -Wextra -pthread`
- Debug: `-g -O0 -DDEBUG`
- Release: `-O3 -DNDEBUG`
- CMake exports compile commands via `CMAKE_EXPORT_COMPILE_COMMANDS=ON`
