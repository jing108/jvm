//
// Created by wands_wang on 2017/11/9.
//

#ifndef CH01_CMD_H
#define CH01_CMD_H

#include <string>
#include <iostream>

class CMD {
private:
    char *cpOption;
    char *className;
    char **args;
    int argc;
    char *usage;
    char *versionInfo;
    char *XjreOption;

    CMD();

public:
    bool helpFlag;
    bool versionFlag;

    static CMD *parseCmd(int argc, char **argv);

    void setUsage(char *usage);

    void printUsage();

    void setVersionInfo(char *versionInfo);

    void printVersionInfo();

    char *getCpOption();

    char *getClass();

    char *printArgs();

    char **getArgs();

    int getArgc();

    char *getJreOption();
};

#endif //CH01_CMD_H
