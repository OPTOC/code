#include <stdio.h>
#include <dirent.h>
#include <string.h>
unsigned int conut = 0;
void listDirectories(const char* path) {
    conut++;
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR || 0) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                const unsigned int size_old = (strlen(path) + strlen(entry->d_name) + 1) * sizeof(char);
                char childPath[size_old];
                snprintf(childPath, sizeof(childPath) + 1, "%s/%s", path, entry->d_name);
                printf("路径:%s    层数%d\n", childPath, conut);
                listDirectories(childPath);
                conut--;
            }
        }
    }
    closedir(dir);
}

int main() {
    const char* rootPath = "/home/zjh/fuse_fuse";
    listDirectories(rootPath);
    return 0;
}
