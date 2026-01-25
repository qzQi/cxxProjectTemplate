#include "logger.h"
#include <iostream>

namespace common {

void Logger::debug(const std::string& msg) {
    log_message("DEBUG", msg);
}

void Logger::info(const std::string& msg) {
    log_message("INFO", msg);
}

void Logger::warn(const std::string& msg) {
    log_message("WARN", msg);
}

void Logger::error(const std::string& msg) {
    log_message("ERROR", msg);
}

void Logger::log_message(const std::string& level, const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "[%Y-%m-%d %H:%M:%S.") 
        << std::setfill('0') << std::setw(3) << ms.count() << "] [" << level << "] " << msg << std::endl;
    
    if (level == "ERROR") {
        std::cerr << oss.str();
    } else {
        std::cout << oss.str();
    }
}

} // namespace common