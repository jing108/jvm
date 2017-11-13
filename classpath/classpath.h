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
};

#endif //CH01_CLASSPATH_H
