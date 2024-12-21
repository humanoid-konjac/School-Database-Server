#include "View.h"
#include <fstream>
#include <sstream>

std::string View::render(const std::string& templateName) {
    std::ifstream file(templateName);
    if (!file.is_open()) {
        return "Error: Unable to open template file.";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
