#include "MyRouter.h"
#include "framework/Router.h"
#include "framework/http.h"
#include "framework/View.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <unordered_map>

extern MyRouter myRouter; // 声明外部的MyRouter对象

SOCKET init(int port = 9870)
{
    // 初始化网络环境
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << ("ERROR: 初始化Winsock失败\n");
        exit(-1);
    }
    cout << ("初始化Winsock: 成功\n");

    // 创建服务端接口
    SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == sockServer) {
        cout << ("ERROR: 创建服务端接口失败\n");
        WSACleanup();
        exit(-1);
    }
    cout << ("创建服务端接口成功\n");

    // 绑定端口号和IP地址
    SOCKADDR_IN addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);  // 端口号  host to net short
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  // 本机地址
    if (bind(sockServer, (sockaddr*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        cout << ("ERROR: 绑定端口号失败\n");
        closesocket(sockServer);
        WSACleanup();
        exit(-1);
    }
    cout << ("绑定端口号成功\n");

    // 监听端口号(告诉操作系统，与当前程序建立逻辑关联)
    if (listen(sockServer, 5) == SOCKET_ERROR) {
        cout << ("监听端口号失败\n");
        closesocket(sockServer);
        WSACleanup();
        exit(-1);
    }
    cout << ("监听端口号成功\n");
    std::cout << "\n当前地址: 127.0.0.1:" << port << "\n\n";

    // 初始化路由器
    myRouter.setupRouting();

    return sockServer;
}

int main() {
    SOCKET sockServer = init(9870);

    while (true) {

        cout << ("等待客户端访问......\n");
        SOCKADDR_IN clientAddr = {};
        int nAddrLen = sizeof(SOCKADDR_IN);
        SOCKET sockClient = accept(sockServer, (sockaddr*)&clientAddr, &nAddrLen);

        if (INVALID_SOCKET == sockClient) {
            cout << ("客户端连接失败\n");
            continue;  // 错误处理后继续等待下一个客户端
        }
        cout << ("成功连接客户端\n");

        // 与客户端通信的循环
        while (true) {

            char szData[1024] = {};
            int ret = recv(sockClient, szData, sizeof(szData) - 1, 0);

            if (ret > 0) {
                szData[ret] = '\0';  // 添加字符串结束符
                cout << ("成功接收客户端数据\n");

                HttpRequest httpRequest;
                httpRequest.analyseRequest(szData);
                
                HttpResponse httpResponse;
                // 使用路由器处理请求
                if(myRouter.handle(httpRequest, httpResponse) != 0)
                {
                    // 处理失败就返回错误界面
                    myRouter.handleError(httpRequest, httpResponse);
                }

                // 发送回显数据               
                string response(httpResponse.toString());
                // cout << endl << httpResponse.toString() << endl << endl;
                ret = send(sockClient, response.c_str(), response.length(), 0);
                if (ret == SOCKET_ERROR) {
                    cout << ("发送数据失败\n");
                    break;  // 发送失败，断开与该客户端的连接
                }
                else cout << "成功完成数据发送\n";
            } else if (ret == 0) {  // 客户端关闭连接
                cout << ("客户端已主动断开连接。\n");
                break;  // 正常退出循环，准备处理下一个客户端
            } else {  // 发生错误
                cout << ("接收客户端数据失败\n");
                break;  // 错误处理后断开连接
            }
        }

        // 关闭客户端套接字
        closesocket(sockClient);
        cout << ("当前客户端已断开连接，等待下一个客户端...\n");
    }

    // 主循环结束后，关闭服务端套接字
    closesocket(sockServer);
    // 清理Winsock资源
    WSACleanup();
    cout << ("资源已清理\n");
    return 0;
}
