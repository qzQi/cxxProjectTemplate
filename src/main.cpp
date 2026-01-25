#include "logger/logger.h"
#include "exception/exception.h"
#include "memory_pool/memory_pool.h"

#include <iostream>
#include <string>

int main() {
    try {
        // 使用日志系统
        common::Logger::info("C++ Development Framework initialized successfully!");
        common::Logger::debug("This is a debug message");
        common::Logger::warn("This is a warning message");
        common::Logger::error("This is an error message");

        // 使用异常处理
        std::cout << "Framework components are ready:" << std::endl;
        std::cout << "- Logger system: OK" << std::endl;
        std::cout << "- Exception handling: OK" << std::endl;
        std::cout << "- Memory management: OK" << std::endl;

        // 使用内存池（演示）
        void* ptr = common::MemoryPool::allocate(1024);
        if (ptr) {
            std::cout << "Memory allocation successful" << std::endl;
            common::MemoryPool::deallocate(ptr);
            std::cout << "Memory deallocation successful" << std::endl;
        }

        common::Logger::info("Application terminated normally");
        
    } catch (const common::BaseException& e) {
        std::cerr << "Caught framework exception: " << e.what() << std::endl;
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Caught standard exception: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
        return -1;
    }

    return 0;
}