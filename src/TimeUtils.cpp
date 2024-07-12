#include "TimeUtils.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>
#include <iostream>

std::string TimeUtils::getCurrentYear()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y");
    return oss.str();
}
std::string TimeUtils::getCurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

std::string TimeUtils::getCurrentMonth()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m");
    return oss.str();
}

std::string TimeUtils::getCurrentTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime = *std::localtime(&now);
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
        std::cerr << "Invalid time format: " << timeStr << std::endl;
        throw std::invalid_argument("Invalid time format");
    }

    if (ss.fail())
    {
        throw std::invalid_argument("Failed to parse time");
    }


    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string TimeUtils::formatTime(const std::chrono::system_clock::time_point &timePoint)
{
    std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm tm = *std::localtime(&timeT);
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
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    return localTime;
}
