#ifndef _ROCK_H_
#define _ROCK_H_

#ifdef __cplusplus
#include <iostream>
#include <cassert>
#include "rocksdb/db.h"

extern "C" {
#endif
#include "fuse_fun.h"
int rocksdb_Fun(DynamicStringArray *diname);
#ifdef __cplusplus
}
#endif
#endif