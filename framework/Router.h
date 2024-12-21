#ifndef ROUTER_FRAMEWORK_H
#define ROUTER_FRAMEWORK_H

#include "http.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define REGISTER_CTRL_FUN(method, path, className, fun) addRouting(method, path, new className(), static_cast<CTRL_FUN>(&className::fun))

class Controller {
public:
    Controller()=default;
    virtual ~Controller() {}
    virtual void handleRequest(const HttpRequest&, HttpResponse&)=0;
};

typedef void (Controller::*CTRL_FUN)(const HttpRequest&, HttpResponse&);

struct RoutingElement
{
    string method;
    string path;
    Controller *object;
    CTRL_FUN fun;
};

class Router
{
public:
    Router();
    virtual ~Router();
    virtual void setupRouting() = 0;
    int handle(const HttpRequest& httpRequest, HttpResponse& httpResponse);

private:
    vector<RoutingElement> table;

protected:
    void addRouting(string method, string path, Controller *obj, CTRL_FUN fun);
};


#endif // ROUTER_FRAMEWORK_H
