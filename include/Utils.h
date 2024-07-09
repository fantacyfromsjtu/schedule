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
    /**
     * @brief 字符串分割函数
     * @param s 输入字符串
     * @param delimiter 分割符
     * @return 返回分割后的字符串向量
     */
    std::vector<std::string> split(const std::string &s, char delimiter);

    /**
     * @brief 读取文件内容
     * @param filename 文件名
     * @return 返回文件内容字符串
     */
    std::string readFile(const std::string &filename);

    /**
     * @brief 将内容写入文件
     * @param filename 文件名
     * @param content 要写入的内容
     */
    void writeFile(const std::string &filename, const std::string &content);

    /**
     * @brief 获取当前时间
     * @return 返回当前时间字符串（格式为YYYY-MM-DD HH:MM:SS）
     */
    std::string getCurrentTime();

    int stringToInt(const std::string &str);

    std::string sha256(const std::string &str);
}

#endif // UTILS_H
