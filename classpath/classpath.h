//
// Created by wands_wang on 2017/11/9.
//

#ifndef CH01_CLASSPATH_H
#define CH01_CLASSPATH_H

#include <zconf.h>
#include <cstdlib>
#include <cstring>

#include "entry.h"

class ClassPath {
private:
    ClassPath();

    void parseBootAndExtClasspath(char *jreOption);

    void parseUserClasspath(char *cpOption);

    char *getJreDir(char *jreOption);

    bool exists(char *path);

public:
    Entry *bootClasspath;
    Entry *extClasspath;
    Entry *userClasspath;

    static ClassPath *parse(char *jreOption, char *cpOption);

    /**
     * 读取class文件
     * @param className 文件名，带.class后缀
     * @param data 存储读取的字节码
     * @return 返回读取的字节数，失败返回-1
     */
    int readClass(char *className, char **data);
};

#endif //CH01_CLASSPATH_H
