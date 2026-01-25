#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <string>

namespace common {

class Logger {
public:
    // 简单的日志函数实现
    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

private:
    static void log_message(const std::string& level, const std::string& msg);
};

} // namespace common