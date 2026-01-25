#pragma once

#include <stdexcept>
#include <string>

namespace common {

// 基础异常类
class BaseException : public std::exception {
public:
    explicit BaseException(const std::string& message) : msg_(message) {}
    virtual ~BaseException() = default;
    
    const char* what() const noexcept override {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

// 配置异常
class ConfigException : public BaseException {
public:
    explicit ConfigException(const std::string& message) : BaseException("Config Error: " + message) {}
};

// 网络异常
class NetworkException : public BaseException {
public:
    explicit NetworkException(const std::string& message) : BaseException("Network Error: " + message) {}
};

// 数据库异常
class DatabaseException : public BaseException {
public:
    explicit DatabaseException(const std::string& message) : BaseException("Database Error: " + message) {}
};

// 内存异常
class MemoryException : public BaseException {
public:
    explicit MemoryException(const std::string& message) : BaseException("Memory Error: " + message) {}
};

} // namespace common