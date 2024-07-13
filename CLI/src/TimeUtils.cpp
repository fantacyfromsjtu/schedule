// TimeUtils.cpp
// 时间工具类函数实现

#include "TimeUtils.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>
#include <iostream>

/**
 * @brief 获取当前年份
 * @return 返回当前年份字符串（格式为YYYY）
 */
std::string TimeUtils::getCurrentYear()
{
    // 获取当前系统时间并转换为std::time_t格式
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    // 将std::time_t转换为std::tm结构
    std::tm localTime = *std::localtime(&now);
    // 使用std::ostringstream格式化时间字符串
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y");
    return oss.str();
}

/**
 * @brief 获取当前日期
 * @return 返回当前日期字符串（格式为YYYY-MM-DD）
 */
std::string TimeUtils::getCurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

/**
 * @brief 获取当前月份
 * @return 返回当前月份字符串（格式为YYYY-MM）
 */
std::string TimeUtils::getCurrentMonth()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m");
    return oss.str();
}

/**
 * @brief 获取当前时间
 * @return 返回当前时间字符串（格式为YYYY-MM-DD HH:MM:SS）
 */
std::string TimeUtils::getCurrentTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

/**
 * @brief 验证日期格式
 * @param date 输入日期字符串
 * @return 格式正确返回true，否则返回false
 */
bool TimeUtils::isValidDate(const std::string &date)
{
    // 使用正则表达式验证日期格式是否为YYYY-MM-DD
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, dateRegex);
}

/**
 * @brief 解析时间字符串
 * @param timeStr 时间字符串（格式为YYYY-MM-DD HH:MM:SS）
 * @return 返回时间点
 */
std::chrono::system_clock::time_point TimeUtils::parseTime(const std::string &timeStr)
{
    std::tm tm = {};
    std::istringstream ss(timeStr);

    // 使用正则表达式验证时间格式
    std::regex timeRegexFull(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    std::regex timeRegexNoSeconds(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");

    if (std::regex_match(timeStr, timeRegexFull))
    {
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    }
    else if (std::regex_match(timeStr, timeRegexNoSeconds))
    {
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        tm.tm_sec = 0; // 默认设置秒为0
    }
    else
    {
        std::cerr << "Invalid time format: " << timeStr << std::endl;
        throw std::invalid_argument("Invalid time format");
    }

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse time");
    }

    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

/**
 * @brief 格式化时间点
 * @param timePoint 时间点
 * @return 返回格式化后的时间字符串（格式为YYYY-MM-DD HH:MM:SS）
 */
std::string TimeUtils::formatTime(const std::chrono::system_clock::time_point &timePoint)
{
    std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm tm = *std::localtime(&timeT);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

/**
 * @brief 验证时间格式
 * @param timeStr 输入时间字符串
 * @return 格式正确返回true，否则返回false
 */
bool TimeUtils::isValidTime(const std::string &timeStr)
{
    std::regex timeRegexFull(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    std::regex timeRegexNoSeconds(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");

    return std::regex_match(timeStr, timeRegexFull) || std::regex_match(timeStr, timeRegexNoSeconds);
}

/**
 * @brief 获取当前系统时间并调整为东八区时间
 * @return 返回当前时间的std::tm结构
 */
std::tm TimeUtils::getLocalTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    return localTime;
}
