#include "http.h"
#include "util.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// HttpRequest 实现
HttpRequest::HttpRequest(const std::string& method, const std::string& uri)
    : m_method(method), m_uri(uri) {}

void HttpRequest::setHeader(const std::string& key, const std::string& value) {
    m_headers[key] = value;
}

std::string HttpRequest::getHeader(const std::string& key) const {
    auto it = m_headers.find(key);
    if (it != m_headers.end()) {
        return it->second;
    }
    return "";
}

std::string HttpRequest::getMethod() const {
    return m_method;
}

std::string HttpRequest::getUri() const {
    return m_uri;
}

std::string HttpRequest::getOriginUri() const {
    return origin_uri;
}

// 解析查询字符串到键值对
std::unordered_map<std::string, std::string> HttpRequest::parseQueryString(const std::string& query) {
    std::unordered_map<std::string, std::string> queryParams;
    std::string::size_type start = 0, end = 0;

    while ((end = query.find('&', start)) != std::string::npos) {
        std::string pair = query.substr(start, end - start);
        std::string::size_type sep = pair.find('=');
        if (sep != std::string::npos) {
            std::string key = pair.substr(0, sep);
            std::string value = pair.substr(sep + 1);
            queryParams[key] = value;
        }
        start = end + 1;
    }

    std::string pair = query.substr(start);
    std::string::size_type sep = pair.find('=');
    if (sep != std::string::npos) {
        std::string key = pair.substr(0, sep);
        std::string value = pair.substr(sep + 1);
        queryParams[key] = value;
    }

    return queryParams;
}

//解析请求的各个部分
void HttpRequest::analyseRequest(char* szData) {
    // 解析HTTP请求头
    std::string request(szData);
    std::string method = request.substr(0, request.find(' '));  // 获取HTTP方法
    std::string fullPath = request.substr(request.find(' ') + 1, request.find(' ', request.find(' ') + 1) - request.find(' ') - 1);  // 获取请求路径
    this->origin_uri = fullPath;

    std::string::size_type queryStart = fullPath.find('?');
    std::string path = (queryStart != std::string::npos) ? fullPath.substr(0, queryStart) : fullPath;  // 获取路径
    std::string query = (queryStart != std::string::npos) ? fullPath.substr(queryStart + 1) : "";  // 获取查询字符串

    // 解析出 ?**=**&**=** 类型的参数
    std::unordered_map<std::string, std::string> queryParams = parseQueryString(query);

    // 解析出 /*****/number 类型的参数
    std::string item;
    std::stringstream ss(path);
    std::getline(ss, item, '/');
    std::getline(ss, item, '/');
    if(item == "scorebystudent")
    {
        std::getline(ss, item, '/');
        std::cout << item << std::endl;
        if(Util::isDigitString(item))
        {
            queryParams["stu_id"] = item;
            size_t pos = path.find_last_of('/');
            if (pos != std::string::npos) {
                path = path.substr(0, pos);
            }
        }
    }
    else if(item == "scorebycourse")
    {
        std::getline(ss, item, '/');
        if(Util::isDigitString(item))
        {
            queryParams["course_id"] = item;
            size_t pos = path.find_last_of('/');
            if (pos != std::string::npos) {
                path = path.substr(0, pos);
            }
        }
    }

    // 修改自身属性 
    this->m_method = method;
    this->m_uri = path;
    for (const auto& [key, value] : queryParams) {
        this->setHeader(key, value);
    }

    //TEST-打印当前请求的方法，路径以及参数
    std::cout << "Method: " << method << "\n";
    std::cout << "Path: " << path << "\n";
    for (const auto& [key, value] : queryParams) {
        std::cout << "Query Parameter: " << key << " = " << value << "\n";
    }
}


// HttpResponse 实现

//初始化响应头
HttpResponse::HttpResponse() {
    m_headers["Content-Type"] = "text/plain";
    m_headers["Connection"] = "close";
    m_headers["Server"] = "chenmaoyuan's CPP server";
    setDateHeader();
}

void HttpResponse::setContentType(const std::string& contentType) {
    m_contentType = contentType;
    m_headers["Content-Type"] = contentType;
}

void HttpResponse::setBody(const std::string& body) {
    m_body = body;
    m_headers["Content-Length"] = std::to_string(body.length());
}

void HttpResponse::setDateHeader() {
    m_headers["Date"] = getCurrentDateTime();
}

std::string HttpResponse::getCurrentDateTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::gmtime(&now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%a, %d %b %Y %H:%M:%S GMT");
    return oss.str();
}

std::string HttpResponse::toString() const {
    std::string response;
    response += "HTTP/1.1 200 OK\r\n";
    for (const auto& header : m_headers) {
        response += header.first + ": " + header.second + "\r\n";
    }
    response += "\r\n" + m_body;
    return response;
}
