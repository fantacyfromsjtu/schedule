#include "TimeUtils.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>

const int SECONDS_PER_HOUR = 3600;
const int EASTERN_8_OFFSET = 8 * SECONDS_PER_HOUR;

std::string TimeUtils::getCurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + EASTERN_8_OFFSET;
    std::tm localTime = *std::gmtime(&now); // 使用 gmtime 将时间转换为 UTC 时间
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

std::string TimeUtils::getCurrentMonth()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + EASTERN_8_OFFSET;
    std::tm localTime = *std::gmtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m");
    return oss.str();
}

std::string TimeUtils::getCurrentTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + EASTERN_8_OFFSET;
    std::tm localTime = *std::gmtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

bool TimeUtils::isValidDate(const std::string &date)
{
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, dateRegex);
}

std::chrono::system_clock::time_point TimeUtils::parseTime(const std::string &timeStr)
{
    std::tm tm = {};
    std::istringstream ss(timeStr);

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
        throw std::invalid_argument("Invalid time format");
    }

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse time");
    }

    // 调整为东八区时间
    std::time_t timeT = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(timeT - EASTERN_8_OFFSET);
}

std::string TimeUtils::formatTime(const std::chrono::system_clock::time_point &timePoint)
{
    std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint) + EASTERN_8_OFFSET;
    std::tm tm = *std::gmtime(&timeT);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

bool TimeUtils::isValidTime(const std::string &timeStr)
{
    std::regex timeRegexFull(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    std::regex timeRegexNoSeconds(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");

    return std::regex_match(timeStr, timeRegexFull) || std::regex_match(timeStr, timeRegexNoSeconds);
}

std::tm TimeUtils::getLocalTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) + EASTERN_8_OFFSET;
    std::tm localTime;
#ifdef _WIN32
    gmtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    return localTime;
}
