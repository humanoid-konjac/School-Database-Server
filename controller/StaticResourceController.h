#ifndef STATIC_RESOURCE_CONTROLLER_H
#define STATIC_RESOURCE_CONTROLLER_H

#include "../framework/Router.h"
#include "../framework/http.h"

class ErrorPageController: public Controller{
public:
    // 渲染 error.html 页面
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;
};

class MainPageController: public Controller{
public:
    // 渲染 index.html 页面
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;
};

class IconController: public Controller{
public:
    // 提供图标文件
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;
};

class CssController: public Controller{
public:
    // 提供 CSS 样式文件
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;
};

#endif