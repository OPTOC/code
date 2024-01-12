#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <zip2.h>

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

    
    // 发送文件夹路径
    char fileName[] = "/home/zjh/thread";
    send(clientSocket, fileName, strlen(fileName) + 1, 0);  // 注意 +1


    // 接收端
    char fileName1[4096] = {0};
    size_t fileName1Size = 0;

    // 读取第一个文件名长度
    read(clientSocket, &fileName1Size, sizeof(fileName1Size));
    // 读取第一个文件名
    read(clientSocket, fileName1, fileName1Size);
    std::cout << "Received file name 1: " << fileName1 << std::endl;

    

    // 打开文件
    std::ofstream outputFile("thread.tar", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // 接收并写入文件
    char buffer[4096] = {0};
    int bytesRead;
    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        // std::cout << "在里面" << std::endl;
        outputFile.write(buffer, bytesRead);
    }
    //解压
    const char *argt[] = { 
        "./zip2",
        "-xf",
        "thread.tar",
        NULL  // 参数数组的末尾必须为NULL
    };
    minitar(sizeof(argt), argt);

    std::cout << "File sent successfully." << std::endl;

    // 关闭套接字和文件
    close(clientSocket);
    outputFile.close();

    return 0;
}
