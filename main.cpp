#include <iostream>
#include "option/cmd.h"
#include "classpath/classpath.h"

void startJVM(CMD *cmd) {

    ClassPath *cp = ClassPath::parse(cmd->getJreOption(), cmd->getCpOption());

    std::cout << "classpath:" << cmd->getCpOption() << "  class:" << cmd->getClass() << "  args:" << cmd->printArgs()
              << std::endl;
}

int main(int argc, char **argv) {
//    CMD *cmd = CMD::parseCmd(argc - 1, &argv[1]);
//    cmd->setUsage(const_cast<char *>("Usage: [-options] class [args...]\n"));
//    cmd->setVersionInfo(const_cast<char *>("version 0.0.1"));
//    if (cmd->versionFlag) {
//        cmd->printVersionInfo();
//    } else if (cmd->helpFlag) {
//        cmd->printUsage();
//    } else {
//        startJVM(cmd);
//    }

//    Zip *zip = Zip::open(argv[1]);
//
//    if (zip) {
//        std::cout << "读取成功" << std::endl;
//    }

    std::string s = "a,b,c,d,";
    std::vector<std::string> strs = split(',', s);

    return 0;
}