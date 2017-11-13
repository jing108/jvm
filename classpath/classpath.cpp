//
// Created by wands_wang on 2017/11/9.
//

#include "classpath.h"

ClassPath::ClassPath()
        : bootClasspath(nullptr),
          extClasspath(nullptr),
          userClasspath(nullptr) {

}

ClassPath *ClassPath::parse(char *jreOption, char *cpOption) {
    auto *cp = new ClassPath;

    cp->parseBootAndExtClasspath(jreOption);
    cp->parseUserClasspath(cpOption);

    return cp;
}

void ClassPath::parseBootAndExtClasspath(char *jreOption) {
    char *jreDir = getJreDir(jreOption);
    bootClasspath = Entry::getEntry(jreDir);

    char *jreLibPath = strcat(jreDir, "/lib/*");
    bootClasspath = Entry::getEntry(jreLibPath);

    char *jreExtPath = strcat(jreDir, "/lib/ext/*");
    extClasspath = Entry::getEntry(jreExtPath);
}

void ClassPath::parseUserClasspath(char *cpOption) {

}

char *ClassPath::getJreDir(char *jreOption) {
    if (jreOption && exists(jreOption)) {
        return jreOption;
    }

    if (exists(const_cast<char *>("./jre"))) {
        return const_cast<char *>("./jre");
    }

    char *javaHome = std::getenv("JAVA_HOME");
    if (javaHome) {
        return strcat(javaHome, "/jre");
    }

    return nullptr;
}

bool ClassPath::exists(char *path) {
    return !access(path, 0);
}
