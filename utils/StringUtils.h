//
// Created by wands_wang on 2017/11/10.
//

#ifndef CH01_STRINGUTILS_H
#define CH01_STRINGUTILS_H

#include <vector>
#include <string>

std::vector<std::string> split(const char &value, const std::string &input) {
    const char *str = input.c_str();
    std::vector<std::string> inputArray;
    int pos = 0;
    for (int i = 0; i < input.size(); i++) {
        if (str[i] == value) {
            char *tmp = static_cast<char *>(malloc(static_cast<size_t>(i - pos + 1)));
            memcpy(tmp, &str[pos], static_cast<size_t>(i - pos));
            tmp[i - pos] = '\0';
            inputArray.emplace_back(tmp);
            pos = i + 1;
        }
    }

    inputArray.push_back(input.substr(pos));

    return inputArray;
}

#endif //CH01_STRINGUTILS_H
