#include <fstream>
#include <sstream>
#include "StaticResourceController.h"
#include "../framework/View.h"
#include "../framework/util.h"

// 渲染 error.html 页面
void ErrorPageController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");
    std::string templateStr = View::render(".\\view\\error.html");
    templateStr = Util::replacePlaceholder(templateStr, "{{url}}", request.getOriginUri());
    response.setBody(templateStr);
}

// 渲染 index.html 页面
void MainPageController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");
    response.setBody(View::render(".\\view\\index.html"));
}

// 提供图标文件
void IconController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    std::ifstream file(".\\public\\images\\favicon.ico", std::ios::binary);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        response.setContentType(Util::getMimeType(request.getUri()));
        response.setBody(buffer.str());
    } else {
        response.setContentType("text/plain");
        response.setBody("Error: Unable to open favicon.ico file.");
    }
}

// 提供 CSS 样式文件
void CssController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    std::ifstream file(".\\public\\css\\main.css");
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        response.setContentType(Util::getMimeType(request.getUri()));
        response.setBody(buffer.str());
    } else {
        response.setContentType("text/plain");
        response.setBody("Error: Unable to open main.css file.");
    }
}