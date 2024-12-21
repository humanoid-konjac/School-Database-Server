#include "util.h"

bool Util::isDigitString(const std::string& str)
{
    if(str == "") return false;
    for(auto& ch : str)
    {
        if(!isdigit(ch))
            return false;
    }
    return true;
}

// 检查字符串是否只包含数字字符
int Util::stringToInt(const std::string& str) {
    if(str == "") return -1;
    for (char c : str) {
        if (!std::isdigit(c)) {
            return -1;
        }
    }
    return std::atoi(str.c_str());
}

std::string Util::replacePlaceholder(std::string templateStr, const std::string& placeholder, const std::string& value) {
    size_t startPos = templateStr.find(placeholder);
    while (startPos != std::string::npos) {
        templateStr.replace(startPos, placeholder.length(), value);
        startPos = templateStr.find(placeholder, startPos + value.length());
    }
    return templateStr;
}

const std::unordered_map<std::string, std::string> Util::mimeTypes = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    {".ico", "image/x-icon"},
    {".json", "application/json"},
    {".txt", "text/plain"}
};

std::string Util::getMimeType(const std::string& path) {
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos) {
        return "application/octet-stream"; // 默认二进制文件
    }

    std::string extension = path.substr(dotPos);
    auto it = mimeTypes.find(extension);
    if (it != mimeTypes.end()) {
        return it->second; // 返回匹配的 MIME 类型
    }

    return "application/octet-stream"; // 未知类型时默认返回
}