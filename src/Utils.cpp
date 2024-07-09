#include "Utils.h"
#include <climits>
std::string Utils::sha256(const std::string &str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int Utils::stringToInt(const std::string &str)
{ // 一个安全的字符串转整数函数，如果不是合法字符串，返回-1
    if (str.empty())
    {
        return -1;
    }

    long long result = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!isdigit(str[i]))
        {
            return -1; // 非数字字符
        }
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX)
        {
            return -1; // 超出 int 范围
        }
    }

    return static_cast<int>(result);
}
