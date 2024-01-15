#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    // 指定 RocksDB 存储路径
    std::string db_path = "/home/zjh/rock";
    rocksdb::Options options;
    options.create_if_missing = true;

    // 列族名字，包括默认列族 "default" 和自定义列族 "my_column_family"
    std::vector<std::string> column_family_names = {"default", "my_column_family"};

    // 打开 RocksDB 数据库
    rocksdb::DB* db;
    rocksdb::Status status;

    // 打开包含列族的数据库
    std::vector<rocksdb::ColumnFamilyDescriptor> column_families;
    std::vector<rocksdb::ColumnFamilyHandle*> column_family_handles;

    for (const auto& column_family_name : column_family_names) {
        column_families.emplace_back(column_family_name, rocksdb::ColumnFamilyOptions());
    }
    cleanup:
    //以只读模式
    // status = rocksdb::DB::OpenForReadOnly(options, db_path, column_families, &column_family_handles, &db);
    //以读写模式
    status = rocksdb::DB::Open(options, db_path, column_families, &column_family_handles, &db);

    // 检查数据库是否成功打开
    if (!status.ok()) {
       std::cerr << "无法打开 RocksDB 数据库，尝试创建: " << std::endl;
       rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);
         // 定义列族
        rocksdb::ColumnFamilyHandle* cf_handle;
        status = db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), column_family_names[1], &cf_handle);
        assert(status.ok());
        delete db;
        goto cleanup;
    }

    // // 在这里进行读写操作，例如写入数据到列族中
    // rocksdb::WriteOptions write_options_cf;
    // status = db->Put(write_options_cf, column_family_handles[1], "key2", "我是好人");
    // assert(status.ok());
    rocksdb::ColumnFamilyHandle* cf_handle = column_family_handles[1]; // 获取列族句柄
    rocksdb::WriteBatch write_options; 
    write_options.Put(cf_handle, "key2", "不是人");
    db->Write(rocksdb::WriteOptions(), &write_options);


    // 查询数据 使用列族句柄进行查询
    std::string value;
    rocksdb::ReadOptions read_options;
    status = db->Get(read_options, column_family_handles[1], "存入最终大小", &value);
    assert(status.ok());
    std::cout << "Value for 存入最终大小: " << value << std::endl;

    // 关闭数据库和列族句柄
    for (auto handle : column_family_handles) {
        status = db->DestroyColumnFamilyHandle(handle);
        assert(status.ok());
    }
    delete db;

    return 0;
}
