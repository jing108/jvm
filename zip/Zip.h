//
// Created by wands_wang on 2017/11/10.
//

#ifndef CH01_ZIP_H
#define CH01_ZIP_H


#include <string>
#include <fstream>
#include <vector>

/**
 * 核心目录 central directory中的file header结构体
 */
#pragma pack(1)
struct CentralFileHeader {
    uint32_t magic = 0x0; //标记 0x02014b50
    uint16_t versionMadeBy = 0x0; //压缩所用的pkware版本
    uint16_t minVersionNeed = 0x0; //解压所需pkware的最低版本
    uint16_t flag = 0x0; //通用位标记
    uint16_t compressionMethod = 0x0; //压缩方法
    uint16_t lastModifyTime = 0x0; //文件最后修改时间
    uint16_t lastModifyDate = 0x0; //文件最后修改日期
    uint32_t crc32 = 0x0; //crc-32校验码
    uint32_t compressedSize = 0x0; //压缩后的大小
    uint32_t uncompressedSize = 0x0; //未压缩的大小
    uint16_t fileNameLength = 0x0; //文件名长度
    uint16_t extFieldLength = 0x0; //扩展域长度
    uint16_t fileCommentLength = 0x0; //文件注释长度
    uint16_t diskNumberStarts = 0x0; //文件开始位置的磁盘编号
    uint16_t inAttributes = 0x0; //内部文件属性
    uint32_t outAttributes = 0x0; //外部文件属性
    uint32_t localHeaderOffset = 0x0; //本地文件头的相对偏移
    char *fileName = nullptr; //文件名
    char *extField = nullptr; //扩展域
    char *fileComment = nullptr; //文件注释
};

class Zip {
public:
    /**
     * 打开一个zip文件
     * @param zipFile
     * @return 返回一个Zip对象指针，如果打开失败，返回nullptr
     */
    static Zip *open(std::string zipFile);

    int fileCount();

private:
    Zip();

    /**
     * 初始化zip文件的各个信息
     * @return 如果成功返回true，失败返回false
     */
    bool init();

    int initCentralFileHeader(int start);

    /**
     * 核心目录中的file header的 magic
     */
    const unsigned char headerInCentralSignature[4] = {0x50, 0x4b, 0x01, 0x02};
    const unsigned char endOfCentralSignature[4] = {0x50, 0x4b, 0x05, 0x06};

    char *raw;
    size_t size;
    std::vector<CentralFileHeader> centralFileHeaders;
};


#endif //CH01_ZIP_H
