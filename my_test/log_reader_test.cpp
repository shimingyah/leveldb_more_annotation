/***************************************************************************
 * 
 * Copyright (c) 2018 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file my_test/log_reader_test.cpp
 * @author zhangying21(zhangying21@baidu.com)
 * @date 2018/12/15 17:21:42
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <iostream>
#include "db/log_reader.h"
#include "leveldb/slice.h"
#include "leveldb/env.h"

int main() {
    leveldb::SequentialFile* file;
    //generate log_writer.data by log_writer_test.cpp
    leveldb::Status status = leveldb::Env::Default()->NewSequentialFile("log_writer.data", &file);
    std::cout << status.ToString() << std::endl;

    leveldb::log::Reader reader(file, NULL, true/*checksum*/, 0/*initial_offset*/);
    // Read all the records and add to a memtable
    std::string scratch;
    leveldb::Slice record;
    while (reader.ReadRecord(&record, &scratch) && status.ok()) {
        std::cout << record.ToString() << std::endl;
    }

    return 0;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 */
