#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 配置服务器地址
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.5.78", &serverAddress.sin_addr);

    // 连接到服务器
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    std::cout << "Connected to server." << std::endl;

    // 发送文件名
    char fileName[] = "example.txt";
    send(clientSocket, fileName, strlen(fileName) + 1, 0);  // 注意 +1

    // 打开文件
    std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // 读取并发送文件内容
    char buffer[1024] = {0};
    int bytesRead;
    while ((bytesRead = inputFile.readsome(buffer, sizeof(buffer))) > 0) {
        send(clientSocket, buffer, bytesRead, 0);
    }

    std::cout << "File sent successfully." << std::endl;

    // 关闭套接字和文件
    close(clientSocket);
    inputFile.close();

    return 0;
}
