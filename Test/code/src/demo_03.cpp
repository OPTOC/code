#include "demo_03.h"
extern unsigned short verbose , Printf_count;
std::mutex mtx; //定义一个锁
std::mutex mtx1; //定义一个锁
struct Time
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> duration;
    Time()
    {
      start = std::chrono::high_resolution_clock::now();
    }
    ~Time()
    {
      end = std::chrono::high_resolution_clock::now();
      duration = end - start;
      float ms = duration.count() * 1000.0f;
      std::cout << "时间 : " << ms << "ms" << std::endl;
    }
};
int rocksdb1_Fun(rocksdb::DB* db, rocksdb::WriteBatch& write_options) {
    db->Write(rocksdb::WriteOptions(), &write_options);
    // 写入完成后清空选项，恢复到默认状态
    write_options.Clear();  
    return 0;
}
void Printf()
{
    // 指定 RocksDB 存储路径
    std::string db_path = "/home/zjh/rock";
    rocksdb::Options options;
    options.create_if_missing = true;

    // 打开 RocksDB 数据库
    rocksdb::DB* db;
    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);

    // 检查数据库是否成功打开
    assert(status.ok());
    if (!status.ok()) {
        std::cerr << "Unable to open RocksDB: " << status.ToString() << std::endl;
    }
    rocksdb::WriteBatch write_options; //定义一个存储数据库数组
    unsigned short count = 0 , count2 = 0 ,  count3 = 0;
    size_t con = 0;
    while(1){
        if(Queuene.count - count> 10 || verbose == 1 ){
            std::lock_guard<std::mutex> lock(mtx);
            count2++;
            while(Queuene.count > 0){
                con++;
                char* path = NULL;
                dequeue(&Queuene,&path);
                write_options.Put(path, "我是好人");
                free(path);
            }  
            if(count2 > 1000 || verbose == 1 )
            {
                rocksdb1_Fun(db, write_options);
                count2 = 0; 
            }
            if(verbose == 1)
                verbose = 2;
        }
        if(verbose == 3){
            con++;
            std::string sju ;
            sju.append(std::to_string(con));
            write_options.Put("存入最终大小",sju);
            std::cout << con << " 最终次数 " << std:: endl;
            rocksdb1_Fun(db, write_options);
            
            break;
        }
    }
    delete db;
}
void Printf2()
{
    while (1)
    {
        if(Queuene2.count > 0)
        {
            
            char* path = NULL;
            {
                std::lock_guard<std::mutex> lock(mtx1);
                dequeue(&Queuene2,&path);  
            }   
            printf("路径:%s \n", path);
            free(path);
        }
        if(verbose == 2 && Queuene2.count  ==  0)
        {
            verbose = 3;
            break;

        }
    } 
}

void thread_demo()
{   
    Time time;
    // 创建多个线程
    std::thread threads(Printf);
    std::thread threads2(erg_thread);
    std::thread threads3(Printf2);
    // 启动线程
    threads.join();
    threads2.join();
    threads3.join();
}
void Lock(struct Queue* q, const char* path)
{
    std::lock_guard<std::mutex> lock(mtx);
    enqueue(q,path);
}
void Lock2(struct Queue* q, const char* path)
{
    std::lock_guard<std::mutex> lock(mtx1);
    enqueue(q,path);
}




