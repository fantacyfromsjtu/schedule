// TimeUtils.h
// 提供时间处理的工具类

#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>

/**
 * @brief 时间工具类，提供处理时间的辅助函数
 */
class TimeUtils
{
public:
    /**
     * @brief 获取当前年份
     * @return 返回当前年份字符串（格式为YYYY）
     */
    static std::string getCurrentYear();

    /**
     * @brief 获取当前日期
     * @return 返回当前日期字符串（格式为YYYY-MM-DD）
     */
    static std::string getCurrentDate();

    /**
     * @brief 获取当前月份
     * @return 返回当前月份字符串（格式为YYYY-MM）
     */
    static std::string getCurrentMonth();

    /**
     * @brief 获取当前时间
     * @return 返回当前时间字符串（格式为YYYY-MM-DD HH:MM:SS）
     */
    static std::string getCurrentTime();

    /**
     * @brief 验证日期格式
     * @param date 输入日期字符串
     * @return 格式正确返回true，否则返回false
     */
    static bool isValidDate(const std::string &date);

    /**
     * @brief 解析时间字符串
     * @param timeStr 时间字符串（格式为YYYY-MM-DD HH:MM:SS）
     * @return 返回时间点
     */
    static std::chrono::system_clock::time_point parseTime(const std::string &timeStr);

    /**
     * @brief 格式化时间点
     * @param timePoint 时间点
     * @return 返回格式化后的时间字符串（格式为YYYY-MM-DD HH:MM:SS）
     */
    static std::string formatTime(const std::chrono::system_clock::time_point &timePoint);

    /**
     * @brief 验证时间格式
     * @param timeStr 输入时间字符串
     * @return 格式正确返回true，否则返回false
     */
    static bool isValidTime(const std::string &timeStr);

private:
    /**
     * @brief 获取当前系统时间并调整为东八区时间
     * @return 返回当前时间的std::tm结构
     */
    static std::tm getLocalTime();
};

#endif // TIMEUTILS_H
