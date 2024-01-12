#include <iostream>
#include <fstream>

void copyZipFile(const std::string& sourcePath, const std::string& destinationPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    if (!sourceFile.is_open()) {
        std::cerr << "Failed to open source ZIP file: " << sourcePath << std::endl;
        return;
    }

    std::ofstream destinationFile(destinationPath, std::ios::binary);
    if (!destinationFile.is_open()) {
        std::cerr << "Failed to open destination ZIP file: " << destinationPath << std::endl;
        sourceFile.close();
        return;
    }

    char buffer[1024];
    while (!sourceFile.eof()) {
        sourceFile.read(buffer, sizeof(buffer));
        std::streamsize bytesRead = sourceFile.gcount();
        destinationFile.write(buffer, bytesRead);
    }

    sourceFile.close();
    destinationFile.close();

    std::cout << "ZIP 文件复制成功!" << std::endl;
}

int main() {
    // 指定源 ZIP 文件路径和目标 ZIP 文件路径
    std::string sourceZipPath = "/home/zjh/thread/123.zip";
    std::string destinationZipPath = "123.zip";

    // 调用复制函数
    copyZipFile(sourceZipPath, destinationZipPath);

    return 0;
}
