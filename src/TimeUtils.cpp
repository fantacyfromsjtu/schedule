#include "TimeUtils.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <regex>

std::tm TimeUtils::getLocalTime()
{
    // 获取当前时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // 转换为 time_t 类型
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // 转换为本地时间结构
    std::tm now_tm = *std::gmtime(&now_time_t);
    // 调整为东八区时间
    now_tm.tm_hour += 8;
    // 修正日期和时间
    std::mktime(&now_tm);
    return now_tm;
}

std::string TimeUtils::getCurrentDate()
{
    std::tm now_tm = getLocalTime();
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d");
    return ss.str();
}

std::string TimeUtils::getCurrentMonth()
{
    std::tm now_tm = getLocalTime();
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m");
    return ss.str();
}

std::string TimeUtils::getCurrentTime()
{
    std::tm now_tm = getLocalTime();
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool TimeUtils::isValidDate(const std::string &date)
{
    // 使用正则表达式验证日期格式是否为YYYY-MM-DD
    std::regex date_regex(R"(\d{4}-\d{2}-\d{2})");
    if (std::regex_match(date, date_regex))
    {
        std::tm tm = {};
        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (!ss.fail())
        {
            return true;
        }
    }
    return false;
}

std::chrono::system_clock::time_point TimeUtils::parseTime(const std::string &timeStr)
{
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail())
    {
        throw std::invalid_argument("Invalid time format");
    }
    tm.tm_hour -= 8; // 调整回 UTC 时间
    std::time_t time_c = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time_c);
}

std::string TimeUtils::formatTime(const std::chrono::system_clock::time_point &timePoint)
{
    std::time_t time_c = std::chrono::system_clock::to_time_t(timePoint);
    std::tm tm = *std::gmtime(&time_c);
    tm.tm_hour += 8; // 调整为东八区时间
    std::mktime(&tm);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
