#ifndef VIEW_H
#define VIEW_H

#include <string>

class View {
public:
    static std::string render(const std::string& templateName);
};

#endif