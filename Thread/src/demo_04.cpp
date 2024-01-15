#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include <iostream>
#include <cassert>

int main() {
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

    // 定义列族
    rocksdb::ColumnFamilyHandle* cf_handle;
    status = db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "my_column_family", &cf_handle);
    assert(status.ok());

    // 插入数据到默认列族
    rocksdb::WriteOptions write_options;
    status = db->Put(write_options, "key1", "value1");
    assert(status.ok());

    // 插入数据到自定义列族
    rocksdb::WriteOptions write_options_cf;
    status = db->Put(write_options_cf, cf_handle, "key2", "value2");
    assert(status.ok());

    // 查询数据
    std::string value;
    rocksdb::ReadOptions read_options;
    status = db->Get(read_options, "key1", &value);
    assert(status.ok());
    std::cout << "Value for key1: " << value << std::endl;

    status = db->Get(read_options, cf_handle, "key2", &value);
    assert(status.ok());
    std::cout << "Value for key2: " << value << std::endl;

    // 关闭列族句柄
    status = db->DestroyColumnFamilyHandle(cf_handle);
    assert(status.ok());

    // 关闭数据库
    delete db;

    return 0;
}
