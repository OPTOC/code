#include <cstdlib>
#include <iostream>

int main() {
    // 执行Shell脚本
    int result = std::system("./123.sh");

    // 检查是否成功执行
    if (result == 0) {
        std::cout << "Shell脚本执行成功!" << std::endl;
    } else {
        std::cerr << "Shell脚本执行失败!" << std::endl;
    }

    return 0;
}
