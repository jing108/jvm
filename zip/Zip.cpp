//
// Created by wands_wang on 2017/11/10.
//

#include "Zip.h"

Zip *Zip::open(std::string zipFile) {
    std::ifstream in(zipFile, std::ios::binary);
    Zip *zip = nullptr;
    if (in.is_open()) {
        zip = new Zip;
        in.seekg(0, std::ios::end);
        zip->size = static_cast<size_t >(in.tellg());
        zip->raw = static_cast<char *>(malloc(zip->size));
        in.seekg(0);
        in.read(zip->raw, zip->size);
        in.close();
        if (zip->init()) {
            return zip;
        }
    }

    return nullptr;
}

Zip::Zip() {

}

bool Zip::init() {
    int i = 0;
    while (i + 4 < size) {
        if (!memcmp(headerInCentralSignature, &raw[i], 4)) {
            i = initCentralFileHeader(i);
        } else {
            i++;
        }
    }
    return true;
}

int Zip::initCentralFileHeader(int start) {
    CentralFileHeader header{};

    memcpy(&header, &raw[start], 46);
    start += 46;

    header.fileName = static_cast<char *>(malloc(header.fileNameLength + 1));
    memset(header.fileName, '\0', header.fileNameLength + 1);
    memcpy(header.fileName, &raw[start], header.fileNameLength);
    start += header.fileNameLength;

    header.extField = static_cast<char *>(malloc(header.extFieldLength + 1));
    memset(header.extField, '\0', header.extFieldLength + 1);
    memcpy(header.extField, &raw[start], header.extFieldLength);
    start += header.extFieldLength;

    header.fileComment = static_cast<char *>(malloc(header.fileCommentLength + 1));
    memset(header.fileComment, '\0', header.fileCommentLength + 1);
    memcpy(header.fileComment, &raw[start], header.fileCommentLength);
    start += header.fileCommentLength;

    centralFileHeaders.push_back(header);

    return start;
}

int Zip::fileCount() {
    return static_cast<int>(centralFileHeaders.size());
}
