#include "ergodic.h"

// #include "rocksdb_wrapper.h"
// #include "log.h"
// #include "debug_log.h"

extern unsigned short verbose ;
std::string kDBPath = "/home/hr/tmnt/db";

static DB *db = nullptr;
static Options options;
std::vector<ColumnFamilyDescriptor> column_families;   // 列族属性向量
std::vector<ColumnFamilyHandle *> handles(2, nullptr); // 列族句柄向量
std::mutex mtx; //定义一个锁
std::mutex mtx1; //定义一个锁

struct Time //求时间
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> duration;
    Time()
    {
      start = std::chrono::high_resolution_clock::now();    //获取创建结构体的时间信息
    }
    ~Time()
    {
      end = std::chrono::high_resolution_clock::now();      //获取删除结构体的时间信息
      duration = end - start;
      float ms = duration.count() * 1000.0f;
      std::cout << "时间 : " << ms << "ms" << std::endl;
    }
};
//将数据写入数据库并清空数组
int rocksdb1_Fun(rocksdb::DB* db, rocksdb::WriteBatch& write_options) {
    db->Write(rocksdb::WriteOptions(), &write_options);
    // 写入完成后清空选项，恢复到默认状态
    write_options.Clear();  
    return 0;
}
/********************线程1***********************/
//负责将数据写入数据库
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
    rocksdb::WriteBatch write_options;                  //定义一个存储数据库数组
    unsigned short count = 0 , count2 = 0 ,  count3 = 0;
    size_t con = 0;
    while(1){
        if(Queuene.count - count> 10 || verbose == 1 ){ //每次读出10个队列  或者 遍历结束
            std::lock_guard<std::mutex> lock(mtx);      //互斥锁
            count2++;
            while(Queuene.count > 0){                   //判断队列是否读完
                con++;
                char* path = NULL;
                dequeue(&Queuene,&path);
                write_options.Put(path, "我是好人");     //写入数据库数组
                free(path);
            }  
            if(count2 > 1000 || verbose == 1 )         //每读10000个数据写入一次数据库
            {
                rocksdb1_Fun(db, write_options);
                count2 = 0; 
            }
            if(verbose == 1)                           //判断遍历是否结束
                verbose = 2;
        }
        if(verbose == 3){                              //遍历结束的收尾工作
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
/********************线程3***********************/
//负责打印日志
void Printf2()
{
    while (1)
    {
        if(Queuene2.count > 0)                          //判断队列中是否还有存在数据
        {
            char* path = NULL;
            {
                std::lock_guard<std::mutex> lock(mtx1); //互斥锁
                dequeue(&Queuene2,&path);               //读出数据  
            }   
            printf("路径:%s \n", path);
            free(path);
        }
        if(verbose == 2 && Queuene2.count  ==  0)       //表示目录已经遍历完成
        {
            verbose = 3;
            break;

        }
    } 
}

void thread_demo()
{   
    Time time; //获取代码运行时间
    // 创建多个线程
    std::thread threads(Printf);
    std::thread threads2(erg_thread);
    std::thread threads3(Printf2);
    // 启动线程
    threads.join();
    threads2.join();
    threads3.join();
}
void Lock(struct Queue* q, const char* path)        //保护入队信息安全
{
    std::lock_guard<std::mutex> lock(mtx);
    enqueue(q,path);
}
void Lock2(struct Queue* q, const char* path)       //保护入队信息安全
{
    std::lock_guard<std::mutex> lock(mtx1);
    enqueue(q,path);
}




