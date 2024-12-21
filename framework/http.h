#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <unordered_map>

class HttpRequest {
public:
    HttpRequest() = default;
    HttpRequest(const std::string& method, const std::string& uri);
    void setHeader(const std::string& key, const std::string& value);
    std::string getHeader(const std::string& key) const;
    std::string getMethod() const;
    std::string getUri() const;
    std::string getOriginUri() const;
    void analyseRequest(char* szData);
    
private:
    std::string origin_uri;
    std::string m_method;
    std::string m_uri;
    std::unordered_map<std::string, std::string> m_headers;
    static std::unordered_map<std::string, std::string> parseQueryString(const std::string& query);
};

class HttpResponse {
public:
    HttpResponse();
    void setContentType(const std::string& contentType);
    void setBody(const std::string& body);
    void setDateHeader();
    std::string toString() const;

private:
    std::string m_contentType;
    std::string m_body;
    std::unordered_map<std::string, std::string> m_headers;
    std::string getCurrentDateTime() const;
};

#endif