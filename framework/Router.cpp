#include "Router.h"
#include "http.h"
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

Router *thisRouter;

Router::Router()
{
    thisRouter = this;
}

Router::~Router() {
    for (auto& route : table) {
        delete route.object;
    }
}

void Router::addRouting(string method, string path, Controller *obj, CTRL_FUN fun)
{
    RoutingElement ele;
    ele.method = method;
    ele.path = path;
    ele.object = obj;
    ele.fun = fun;
    table.push_back(ele);
}

int Router::handle(const HttpRequest& httpRequest, HttpResponse& httpResponse)
{
    string method;
    string path;
    std::unordered_map<std::string, std::string> queryParams;

    for (size_t i = 0; i < table.size(); i++)
    {
        if (table[i].method == httpRequest.getMethod() && table[i].path == httpRequest.getUri())
        {
            // 找到对应的 Controller
            ((*table[i].object).*(table[i].fun))(httpRequest, httpResponse);
            return 0;
        }
    }
    // 报错 找不到适当的 Controller 
    return -1;
}