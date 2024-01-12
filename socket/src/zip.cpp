#include <iostream>
#include <cstdlib>

void compressFolder(const std::string& folderPath, const std::string& compressedFile) {
    std::string command = "tar -czf " + compressedFile + " -C " + folderPath + " .";

    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "压缩失败" << std::endl;
    } else {
        std::cout << "压缩完成: " << compressedFile << std::endl;
    }
}

void decompressFolder(const std::string& compressedFile, const std::string& outputFolder) {
    std::string command = "tar -xzf " + compressedFile + " -C " + outputFolder;

    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "解压失败" << std::endl;
    } else {
        std::cout << "解压完成到: " << outputFolder << std::endl;
    }
}

int main() {
    // 压缩文件夹下所有文件到一个 tar.gz 压缩包中
    const std::string inputFolder = "/home/zjh/thread/";
    const std::string compressedFile = "compressed_file.tar.gz";

    compressFolder(inputFolder, compressedFile);

    // 解压缩 tar.gz 压缩包到指定文件夹
    const std::string outputFolder = "/path/to/your/output/folder/";
    decompressFolder(compressedFile, outputFolder);

    return 0;
}
