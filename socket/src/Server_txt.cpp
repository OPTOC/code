#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>

#define ALLOWED_IP "192.168.5.140"  // 你允许的客户端 IP 地址
#define PORT 8080

void listDirectories(const char* path, int newSocket) {
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return ;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        //判断是否为.  .. 目录 
        if (entry->d_type != DT_DIR) {
            std::string filePath = std::string(path) + '/' + entry->d_name;
            std::cout << "Received file name: " << filePath << std::endl;
            std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
            if (!inputFile.is_open()) {
                std::cerr << "Error opening file." << std::endl;
                close(newSocket);
                exit(EXIT_FAILURE);
            }

            // 读取并发送文件内容
            char buffer[1024] = {0};
            int bytesRead;
            while ((bytesRead = inputFile.readsome(buffer, sizeof(buffer))) > 0) {
                std::cout << "在里面" << std::endl;
                send(newSocket, buffer, bytesRead, 0);
            }

            std::cout << "File received successfully." << std::endl;
            inputFile.close();
        }
        else 
        {
            // std::string filePath = std::string(path) + '/' + entry->d_name;
            // directory.append(std::string("/")+std::string(entry->d_name));
            // send(newSocket, directory.c_str(), directory.size() + 1, 0);
        }
    }
    // send(newSocket, "END_FOLDER", sizeof("END_FOLDER"), 0);
    closedir(dir);
    
}

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

    std::string file_Path = std::string(fileName);
    size_t lastSlashPos = file_Path.find_last_of('/');
    std::string directory = file_Path.substr(lastSlashPos+1);
    size_t dirSize = directory.size() + 1;
    send(newSocket, &dirSize, sizeof(dirSize), 0);
    send(newSocket, directory.c_str(), dirSize, 0);

    listDirectories(fileName, newSocket);
   

    // 关闭套接字和文件
    close(newSocket);
    close(serverSocket);
    

    return 0;
}
