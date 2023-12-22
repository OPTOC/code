#include "demo_02.h"
int rocksdb_Fun(void) {
    // 指定 RocksDB 存储路径
    std::string db_path = "/home/zjh/rock";

    // RocksDB 的选项配置
    rocksdb::Options options;
    options.create_if_missing = true;

    // 打开 RocksDB 数据库
    rocksdb::DB* db;
    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);

    // 检查数据库是否成功打开
    assert(status.ok());
    if (!status.ok()) {
        std::cerr << "Unable to open RocksDB: " << status.ToString() << std::endl;
        return 1;
    }

    // 写入数据
    rocksdb::WriteOptions write_options;
    status = db->Put(write_options, "key1", "5789");
    status = db->Put(write_options, "key2", "91011");
    // 检查数据是否成功写入
    assert(status.ok());
    if (!status.ok()) {
        std::cerr << "Error writing to RocksDB: " << status.ToString() << std::endl;
        delete db;
        return 1;
    }

    //读取数据
    rocksdb::ReadOptions read_options;
    std::string value;
    status = db->Get(read_options, "key1", &value);

    // 检查数据是否成功读取
    assert(status.ok());
    if (status.ok()) {
        std::cout << "Value for key1: " << value << std::endl;
    } else {
        std::cerr << "Error reading from RocksDB: " << status.ToString() << std::endl;
    }
    status = db->Get(read_options, "key2", &value);
    // 检查数据是否成功读取
    assert(status.ok());
    if (status.ok()) {
        std::cout << "Value for key2: " << value << std::endl;
    } else {
        std::cerr << "Error reading from RocksDB: " << status.ToString() << std::endl;
    }

    // 使用 RocksDB 迭代器遍历数据库中的所有键值对
    rocksdb::Iterator* it = db->NewIterator(read_options);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << "Key: " << it->key().ToString() << ", Value: " << it->value().ToString() << std::endl;
    }
    delete it;

    // 关闭 RocksDB 数据库
    delete db;

    return 0;
}

