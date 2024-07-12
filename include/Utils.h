#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <mutex>
#include <openssl/evp.h>
namespace Utils
{

    extern std::mutex mtx;
    int stringToInt(const std::string &str);

    std::string getTaskFile(const std::string &username);
    std::string sha256(const std::string &str);
    void setColor(const std::string &colorCode);
    void resetColor();
    void printSeparator();
    void printBold(const std::string &text);
}

#endif // UTILS_H
