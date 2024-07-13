// Utils.cpp
// 实用工具函数的实现

#include "Utils.h"
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>

namespace Utils
{
    std::mutex mtx; // 定义全局互斥锁，用于线程同步

    /**
     * @brief 生成字符串的SHA256哈希值
     * @param str 输入字符串
     * @return SHA256哈希值
     */
    std::string sha256(const std::string &str)
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

    /**
     * @brief 将字符串转换为整数
     * @param str 要转换的字符串
     * @return 转换后的整数，如果转换失败返回-1
     */
    int stringToInt(const std::string &str)
    {
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

    /**
     * @brief 获取任务文件的路径
     * @param username 用户名
     * @return 任务文件路径
     */
    std::string getTaskFile(const std::string &username)
    {
        return "../data/tasks/" + username + "_task.txt";
    }

    /**
     * @brief 设置终端输出颜色
     * @param colorCode 颜色代码
     */
    void setColor(const std::string &colorCode)
    {
        std::cout << "\033[" << colorCode << "m";
    }

    /**
     * @brief 重置终端输出颜色
     */
    void resetColor()
    {
        std::cout << "\033[0m";
    }

    /**
     * @brief 打印分割线
     */
    void printSeparator()
    {
        std::cout << "------------------------------------------------------" << std::endl;
    }

    /**
     * @brief 打印加粗文本
     * @param text 要打印的文本
     */
    void printBold(const std::string &text)
    {
        std::cout << "\033[1m" << text << "\033[0m";
    }
}
