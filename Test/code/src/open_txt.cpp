#include "open_txt.h"
int open_txt(std::string& path, const std::string& filePath ) {
    // 文件路径
    // std::string filePath = "../text/file.txt";

    // 要查找的内容
    std::string searchContent = "path:"; // 替换为你要查找的内容

    // 尝试打开文件
    std::fstream file(filePath);
 //ifstream打开的只能读  ofstream打开的只能写 ifstream可读写
    // 检查文件是否成功打开  如果创建一个新的文件
    if (!file.is_open()) {
        std::cerr << "File not found: " << filePath << std::endl;
        // 创建文件并写入默认内容
        std::ofstream newFile(filePath);
            newFile << "path:/home/zjh/mount/zjh2" << std::endl; //向文件中写入内容
            newFile.close();
            std::cout << "New file created with default content." << std::endl;      
        // 重新打开文件
        file.open(filePath);
    }
    bool found = false; // 用于标记是否找到内容
    // 逐行读取文件内容并检查是否包含特定内容
    std::string line;
    while (std::getline(file, line)) {
        size_t foundPos = line.find(searchContent); //得到找到位置的第一个偏移量
        if (foundPos != std::string::npos) {
            path = line.substr(foundPos + searchContent.length());//找到该词,并打印该词后面的数据
            std::cout << "Found: " << path << std::endl;
            found = true;
        }
    }
    // file.clear(); //得先清除一下 因为std::getline(file, line)写入结束标志（EOF）
    // file.seekp(0, std::ios::end);//偏移到文件尾端
    // file << "我是坏人" << std::endl;//添加文本数据
    // 如果没有找到内容，输出提示
    if (!found) {
        std::cout << "The specified content was not found in the file." << std::endl;
    }
    // 关闭文件
    file.close();

    return 0;
}