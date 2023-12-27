#include "open_txt.h"
int open_txt(std::string& path) {
    // 文件路径
    std::string filePath = "../text/file.txt";

    // 要查找的内容
    std::string searchContent = "path:"; // 替换为你要查找的内容

    // 尝试打开文件
    std::ifstream file(filePath);

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return -1;
    }
    bool found = false; // 用于标记是否找到内容
    // 逐行读取文件内容并检查是否包含特定内容
    std::string line;
    while (std::getline(file, line)) {
        size_t foundPos = line.find(searchContent);
        if (foundPos != std::string::npos) {
            // std::string contentSnippet = line.substr(foundPos, searchContent.length());//找到该词并打印出来
            path = line.substr(foundPos + searchContent.length());//找到该词,并打印该词后面的数据
            std::cout << "Found: " << path << std::endl;
            found = true;
        }
    }
    // 如果没有找到内容，输出提示
    if (!found) {
        std::cout << "The specified content was not found in the file." << std::endl;
    }

    // 关闭文件
    file.close();

    return 0;
}