#ifndef _OPEN_TXT_H_
#define _OPEN_TXT_H_
// #ifdef __cplusplus
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
// #include <experimental/filesystem>
#include <unistd.h>
// extern "C" {
// #endif
int open_txt(std::string& path, const std::string& filePath = "../text/file.txt");
// #ifdef __cplusplus
// }
// #endif
#endif