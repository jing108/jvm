//
// Created by wands_wang on 2017/11/9.
//

#ifndef CH01_ENTRY_H
#define CH01_ENTRY_H

#include <utility>
#include <fstream>
#include <vector>

class WildcardEntry;

class DirEntry;

class CompositeEntry;

class ZipEntry;

class Entry {
public:
    explicit Entry(std::string path);

    virtual int readClass(std::string className, char **data) = 0;

    static Entry *getEntry(std::string path);

    std::string path;
};

class WildcardEntry : public Entry {
public:
    explicit WildcardEntry(const std::string &path);

    int readClass(std::string className, char **data);

};

class DirEntry : public Entry {
public:
    explicit DirEntry(const std::string &path);

    int readClass(std::string className, char **data);
};

class CompositeEntry : public Entry {
public:
    explicit CompositeEntry(const std::string &path);

    int readClass(std::string className, char **data);

private:
    std::vector<Entry *> entries;
};

class ZipEntry : public Entry {
public:
    explicit ZipEntry(const std::string &path);

    int readClass(std::string className, char **data);
};

#endif //CH01_ENTRY_H
