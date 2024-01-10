#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 配置服务器地址
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "192.168.5.78", &serverAddress.sin_addr);

    // 连接到服务器
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // 接收数据
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::cout << "Server says: " << buffer << std::endl;

    // 关闭套接字
    close(clientSocket);

    return 0;
}

