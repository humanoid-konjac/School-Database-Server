#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <unordered_map>

class Util {
public:
    static int stringToInt(const std::string& str);
    static bool isDigitString(const std::string& str);
    static std::string replacePlaceholder(std::string templateStr, const std::string& placeholder, const std::string& value);
    
    static const std::unordered_map<std::string, std::string> mimeTypes;
    static std::string getMimeType(const std::string& path);
};

#endif
