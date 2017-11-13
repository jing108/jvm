//
// Created by wands_wang on 2017/11/9.
//

#include "cmd.h"

CMD::CMD() : argc(0),
             helpFlag(false),
             versionFlag(false),
             cpOption(nullptr),
             className(nullptr),
             args(nullptr),
             usage(nullptr),
             versionInfo(nullptr),
             XjreOption(nullptr) {
};

CMD *CMD::parseCmd(int argc, char **argv) {
    auto *cmd = new CMD;
    if (argc > 0) {
        int index = 0;
        while (index < argc) {
            char *param = argv[index];
            if (!strcmp(param, "-version")) {
                cmd->versionFlag = true;
                break;
            } else if (!strcmp(param, "-help")) {
                cmd->helpFlag = true;
                break;
            } else if (!strcmp(param, "-cp") || !strcmp(param, "-classpath")) {
                index++;
                size_t len = strlen(argv[index]) + 1;
                cmd->cpOption = static_cast<char *>(malloc(len));
                memcpy(cmd->cpOption, argv[index + 1], len);
                index++;
            } else if (param[0] != '-' && !cmd->className) {
                size_t len = strlen(param) + 1;
                cmd->className = static_cast<char *>(malloc(len));
                memcpy(cmd->className, param, len);
                //解析类的成员函数
                index++;
                while (index < argc && argv[index][0] != '-') {
                    cmd->argc++;
                    index++;
                }
                cmd->args = static_cast<char **>(malloc(sizeof(char *) * cmd->argc));
                memset(cmd->args, 0x0, sizeof(char *) * cmd->argc);
                for (int i = 0; i < cmd->argc; i++) {
                    size_t strLen = strlen(argv[index - cmd->argc + i]) + 1;
                    cmd->args[i] = static_cast<char *>(malloc(strLen));
                    memcpy(cmd->args[i], argv[index - cmd->argc + i], strLen);
                }
            } else if (!strcmp("-Xjre", param)) {
                index++;
                size_t len = strlen(argv[index]) + 1;
                cmd->XjreOption = static_cast<char *>(malloc(len));
                memcpy(cmd->XjreOption, argv[index], len);
                index++;
            } else {
                cmd->helpFlag = true;
                break;
            }
        }
    } else {
        cmd->helpFlag = true;
    }

    return cmd;
}

void CMD::setUsage(char *usage) {
    if (usage) {
        size_t len = strlen(usage) + 1;
        this->usage = static_cast<char *>(malloc(len));
        memcpy(this->usage, usage, len);
    }
}

void CMD::printUsage() {
    if (usage) {
        std::cout << usage << std::endl;
    }
}

void CMD::setVersionInfo(char *versionInfo) {
    if (versionInfo) {
        size_t len = strlen(versionInfo) + 1;
        this->versionInfo = static_cast<char *>(malloc(len));
        memcpy(this->versionInfo, versionInfo, len);
    }
}

void CMD::printVersionInfo() {
    if (versionInfo) {
        std::cout << versionInfo << std::endl;
    }
}

char *CMD::getCpOption() {
    return cpOption;
}

char *CMD::getClass() {
    return className;
}

char *CMD::getJreOption() {
    return XjreOption;
}

int CMD::getArgc() {
    return argc;
}

char **CMD::getArgs() {
    return args;
}

char *CMD::printArgs() {
    size_t len = 0;
    for (int i = 0; i < argc; i++) {
        len = len + strlen(args[i]) + 1 + 2;
    }
    auto *str = static_cast<char *>(malloc(len));
    memset(str, '\0', len);
    for (int i = 0; i < argc; i++) {
        strcat(str, args[i]);
        strcat(str, "  ");
    }

    return str;
}
