#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 创建套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // 配置服务器地址
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    int clientSocket;
    // 绑定地址
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // 监听连接
    while(1){
    listen(serverSocket, 5);
    std::cout << "Server listening on port 8080..." << std::endl;  
    // 接受连接
    clientSocket = accept(serverSocket, NULL, NULL);
    // 发送数据
    static int a = 0;
     a++;
     std::string asd = "你好，客户端！";
     asd.append(std::to_string(a));
    send(clientSocket, asd.c_str(), asd.size(), 0);
    }
    // 关闭套接字
    close(serverSocket);
    close(clientSocket);


    return 0;
}

