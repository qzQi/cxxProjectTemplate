// common/src/yamlParser/yaml_parser.cpp
#include "yaml_parser.h"
#include <fstream>
#include <sstream>

namespace common {

bool YamlParser::parseFile(const std::string& filepath, std::map<std::string, std::string>& out) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // 简单的YAML解析实现
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            
            // 清理空白字符
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            out[key] = value;
        }
    }
    
    return true;
}

bool YamlParser::parseString(const std::string& yamlContent, std::map<std::string, std::string>& out) {
    std::istringstream stream(yamlContent);
    std::string line;
    
    while (std::getline(stream, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            out[key] = value;
        }
    }
    
    return true;
}

template<typename T>
T YamlParser::getValue(const std::map<std::string, std::string>& config, const std::string& key, T defaultValue) {
    auto it = config.find(key);
    if (it != config.end()) {
        // 简单转换
        if constexpr (std::is_same_v<T, std::string>) {
            return it->second;
        } else if constexpr (std::is_same_v<T, int>) {
            return std::stoi(it->second);
        } else if constexpr (std::is_same_v<T, double>) {
            return std::stod(it->second);
        } else if constexpr (std::is_same_v<T, bool>) {
            return it->second == "true" || it->second == "True" || it->second == "TRUE";
        }
    }
    return defaultValue;
}

// 显式模板实例化
template std::string YamlParser::getValue<std::string>(const std::map<std::string, std::string>&, const std::string&, std::string);
template int YamlParser::getValue<int>(const std::map<std::string, std::string>&, const std::string&, int);
template double YamlParser::getValue<double>(const std::map<std::string, std::string>&, const std::string&, double);
template bool YamlParser::getValue<bool>(const std::map<std::string, std::string>&, const std::string&, bool);

} // namespace common