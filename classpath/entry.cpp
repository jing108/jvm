//
// Created by wands_wang on 2017/11/9.
//

#include "entry.h"

Entry::Entry(std::string path) {
    this->path = std::move(path);
}

Entry *Entry::getEntry(std::string path) {
    if (path.find(':') != std::string::npos) {
        return new CompositeEntry(path);
    }
    if (path.at(path.length() - 1) == '*') {
        return new WildcardEntry(path);
    }
    size_t len = path.length();
    if (path.rfind(".jar") == len - 4 || path.rfind(".JAR") == len - 4 || path.rfind(".zip") == len - 4 ||
        path.rfind(".ZIP") == len - 4) {
        return new ZipEntry(path);
    }

    return new DirEntry(path);
}

WildcardEntry::WildcardEntry(const std::string &path) : Entry(path) {}

int WildcardEntry::readClass(std::string className, char **data) {
    return 0;
}

DirEntry::DirEntry(const std::string &path) : Entry(path) {
}

int DirEntry::readClass(std::string className, char **data) {
    if (path.back() != '/') {
        path.append("/");
    }
    path.append(className);
    std::ifstream in(path, std::ios::binary);
    if (in.is_open()) {
        in.seekg(0, std::ios::end);
        auto size = static_cast<size_t>(in.tellg());
        in.seekg(0);
        *data = static_cast<char *>(malloc(size));
        in.read(*data, size);

        in.close();
        return 0;
    } else {
        return 1;
    }
}

CompositeEntry::CompositeEntry(const std::string &path) : Entry(path) {
    std::vector<std::string> paths = split(':', path);

    for (int i = 0; i < paths.size(); i++) {
        entries.push_back(Entry::getEntry(paths[i]));
    }
}

int CompositeEntry::readClass(std::string className, char **data) {
    for (int i = 0; i < entries.size(); i++) {
        if (!entries[i]->readClass(className, data)) {
            return 0;
        }
    }

    return -1;
}

ZipEntry::ZipEntry(const std::string &path) : Entry(path) {

}

int ZipEntry::readClass(std::string className, char **data) {
    return 0;
}
