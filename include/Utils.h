#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
namespace Utils
{

    int stringToInt(const std::string &str);

    std::string sha256(const std::string &str);
}

#endif // UTILS_H
