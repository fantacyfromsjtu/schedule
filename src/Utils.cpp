#include "Utils.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
namespace Utils
{
    std::mutex mtx;
    std::string
    sha256(const std::string &str)
    {
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int lengthOfHash = 0;

        // 创建并初始化 EVP_MD_CTX
        EVP_MD_CTX *context = EVP_MD_CTX_new();
        EVP_DigestInit_ex(context, EVP_sha256(), nullptr);
        EVP_DigestUpdate(context, str.c_str(), str.size());
        EVP_DigestFinal_ex(context, hash, &lengthOfHash);
        EVP_MD_CTX_free(context);

        // 将结果转换为十六进制字符串表示
        std::stringstream ss;
        for (unsigned int i = 0; i < lengthOfHash; ++i)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        return ss.str();
    }

    int stringToInt(const std::string &str)
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

    std::string getTaskFile(const std::string &username)
    {
        return "../data/tasks/" + username + "_task.txt";
    }

    void setColor(const std::string &colorCode)
    {
        std::cout << "\033[" << colorCode << "m";
    }

    void resetColor()
    {
        std::cout << "\033[0m";
    }

    void printSeparator()
    {
        std::cout << "------------------------------------------------------" << std::endl;
    }
    void printBold(const std::string &text)
    {
        std::cout << "\033[1m" << text << "\033[0m";
    }
}