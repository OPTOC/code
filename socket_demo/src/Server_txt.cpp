#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ALLOWED_IP "192.168.5.140"  // 你允许的客户端 IP 地址
#define PORT 8080

int main() {
    // 创建套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int newSocket;
     
    // 配置服务器地址
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    socklen_t addrSize = sizeof(serverAddress);

    // 绑定地址
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // 监听连接
    listen(serverSocket, 5);
    std::cout << "Server listening on port " << PORT << "..." << std::endl;  

    // 接受连接
    if ((newSocket = accept(serverSocket, (struct sockaddr*)&serverAddress, &addrSize)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // 检查连接是否来自允许的 IP 地址
    if (strcmp(inet_ntoa(serverAddress.sin_addr), ALLOWED_IP) != 0) {
        std::cerr << "Connection from unauthorized IP address. Closing connection." << std::endl;
        close(newSocket);
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted from " << inet_ntoa(serverAddress.sin_addr) << ":" << ntohs(serverAddress.sin_port) << std::endl;

    // 读取文件名
    char fileName[1024] = {0};
    read(newSocket, fileName, sizeof(fileName));
    std::cout << "Received file name: " << fileName << std::endl;

    // 打开文件
    std::ofstream outputFile(fileName, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        close(newSocket);
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // 接收并写入文件
    char buffer[1024] = {0};
    int bytesRead;
    while ((bytesRead = read(newSocket, buffer, sizeof(buffer))) > 0) {
        outputFile.write(buffer, bytesRead);
    }

    std::cout << "File received successfully." << std::endl;

    // 关闭套接字和文件
    close(newSocket);
    close(serverSocket);
    outputFile.close();

    return 0;
}
