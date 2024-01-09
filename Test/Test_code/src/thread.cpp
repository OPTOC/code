#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
bool data_ready = false;

void producer() {
    while (true) {
        // 生产数据
        // ...

        // 使用互斥量锁定共享资源
        {
            std::lock_guard<std::mutex> lock(mtx);

            // 更新共享数据
            data_ready = true;
            std::cout << "producer 线程正在运行..." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void consumer() {
    while (true) {
        // 使用互斥量锁定共享资源
        {
            std::lock_guard<std::mutex> lock(mtx);

            if (data_ready) {
                // 消费数据
                // ...
                std::cout << "数据已被消费" << std::endl;

                // 重置标志
                data_ready = false;
            }

            std::cout << "consumer 线程正在运行..." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // 创建生产者和消费者线程
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    // 等待线程完成
    producer_thread.join();
    consumer_thread.join();
    while (1)
    {
         printf("我是好人");
    }
    
   
    // std::cin.get();
    return 0;
}
