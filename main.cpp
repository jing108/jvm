#include <iostream>
#include <iomanip>
#include "option/cmd.h"
#include "classpath/classpath.h"
#include "classfile/ClassFile.h"
#include "rtda/frame.h"

void startJVM(CMD *cmd) {

    ClassPath *cp = ClassPath::parse(cmd->getJreOption(), cmd->getCpOption());
    char *data;
    cp->readClass(cmd->getClass(), &data);

    std::cout << "classpath:" << cmd->getCpOption() << "  class:" << cmd->getClass() << "  args:" << cmd->printArgs()
              << std::endl;
}

void testLocalVars(LocalVars *vars) {
    vars->setInt(0, 100);
    vars->setInt(1, -100);
    vars->setLong(2, 2997924580);
    vars->setLong(4, -2997924580);
    vars->setFloat(6, 3.1415926f);
    vars->setDouble(7, 2.71828182845);
    vars->setRef(9, nullptr);

    std::cout << vars->getInt(0) << std::endl;
    std::cout << vars->getInt(1) << std::endl;
    std::cout << vars->getLong(2) << std::endl;
    std::cout << vars->getLong(4) << std::endl;
    std::cout << std::fixed << std::setprecision(7) << vars->getFloat(6) << std::endl;
    std::cout << std::fixed << std::setprecision(11) << vars->getDouble(7) << std::endl;
    std::cout << std::fixed << vars->getRef(9) << std::endl;
}

void testOperandStack(OperandStack *ops) {
    ops->pushInt(100);
    ops->pushInt(-100);
    ops->pushLong(2997924580);
    ops->pushLong(-2997924580);
    ops->pushFloat(3.1415926f);
    ops->pushDouble(2.71828182845);
    ops->pushRef(nullptr);

    std::cout << std::fixed << ops->popRef() << std::endl;
    std::cout << std::fixed << std::setprecision(11) << ops->popDouble() << std::endl;
    std::cout << std::fixed << std::setprecision(7) << ops->popFloat() << std::endl;
    std::cout << ops->popLong() << std::endl;
    std::cout << ops->popLong() << std::endl;
    std::cout << ops->popInt() << std::endl;
    std::cout << ops->popInt() << std::endl;

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

    Frame *frame = new Frame(100, 100);

    testLocalVars(&frame->localVars);
    testOperandStack(frame->operandStack);

    return 0;
}