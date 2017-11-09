#include <iostream>
#include "option/cmd.h"

void startJVM(CMD *cmd) {
    std::cout << "classpath:" << cmd->getClassPath() << "  class:" << cmd->getClass() << "  args:" << cmd->printArgs()
              << std::endl;
}

int main(int argc, char **argv) {
    CMD *cmd = CMD::parseCmd(argc - 1, &argv[1]);
    cmd->setUsage(const_cast<char *>("Usage: [-options] class [args...]\n"));
    cmd->setVersionInfo(const_cast<char *>("version 0.0.1"));
    if (cmd->versionFlag) {
        cmd->printVersionInfo();
    } else if (cmd->helpFlag) {
        cmd->printUsage();
    } else {
        startJVM(cmd);
    }

    return 0;
}