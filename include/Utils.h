// Utils.h
// 实用工具函数和变量的声明

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
    extern std::mutex mtx; // 全局互斥锁，用于线程同步

    /**
     * @brief 将字符串转换为整数
     * @param str 要转换的字符串
     * @return 转换后的整数，如果转换失败返回-1
     */
    int stringToInt(const std::string &str);

    /**
     * @brief 获取任务文件的路径
     * @param username 用户名
     * @return 任务文件路径
     */
    std::string getTaskFile(const std::string &username);

    /**
     * @brief 生成字符串的SHA256哈希值
     * @param str 输入字符串
     * @return SHA256哈希值
     */
    std::string sha256(const std::string &str);

    /**
     * @brief 设置终端输出颜色
     * @param colorCode 颜色代码
     */
    void setColor(const std::string &colorCode);

    /**
     * @brief 重置终端输出颜色
     */
    void resetColor();

    /**
     * @brief 打印分割线
     */
    void printSeparator();

    /**
     * @brief 打印加粗文本
     * @param text 要打印的文本
     */
    void printBold(const std::string &text);
}

#endif // UTILS_H
