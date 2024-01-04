#include <iostream>
#include <thread>

// 函数，将在新线程中执行
void threadFunction() {//int id
    using namespace std::literals::chrono_literals; 
    while(1){
        std::cout << "Hello from thread:我是一号 " << std::endl;
        std::this_thread::sleep_for(0.5s);
        // std::cin.get();
    }
}
// 函数，将在新线程中执行
void threadFunction2() {//int id
    using namespace std::literals::chrono_literals; 
    while(1){
        std::cout << "Hello or from thread:我是二号 " << std::endl;
        std::this_thread::sleep_for(0.51s);
    }
}

int main() {
    // 创建多个线程
    std::thread threads(threadFunction);
    std::thread threads2(threadFunction2);
    // 启动线程
    threads.join();
    threads2.join();

    std::cout << "All threads joined." << std::endl;

    std::cin.get();
    return 0;
}
