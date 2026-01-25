// common/src/yamlParser/yaml_parser.h
#pragma once

#include <string>
#include <map>
#include <vector>

namespace common {

class YamlParser {
public:
    // 解析YAML文件
    static bool parseFile(const std::string& filepath, std::map<std::string, std::string>& out);
    
    // 解析YAML字符串
    static bool parseString(const std::string& yamlContent, std::map<std::string, std::string>& out);
    
    // 获取配置值
    template<typename T>
    static T getValue(const std::map<std::string, std::string>& config, const std::string& key, T defaultValue);
};

} // namespace common