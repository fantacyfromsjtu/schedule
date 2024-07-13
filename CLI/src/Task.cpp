#include "Task.h"
#include "Utils.h"

/**
 * @brief 构造函数，初始化任务属性
 * @param id 任务ID
 * @param name 任务名称
 * @param startTime 任务开始时间（格式为YYYY-MM-DD HH:MM:SS）
 * @param priority 任务优先级（默认中等）
 * @param category 任务分类（默认一般）
 * @param reminderTime 提醒时间（格式为YYYY-MM-DD HH:MM:SS）
 * @param reminded 是否已经提醒
 */
Task::Task(int id, const std::string &name, const std::string &startTime,
           const std::string &priority, const std::string &category,
           const std::string &reminderTime, const bool &reminded)
{
    this->id = id;
    this->name = name;
    this->startTime = TimeUtils::parseTime(startTime);
    this->priority = priority;
    this->category = category;
    if (!reminderTime.empty())
    {
        this->reminderTime = TimeUtils::parseTime(reminderTime);
    }
    else
    {
        this->reminderTime = this->startTime;
    }
    this->reminded = reminded;
}

/**
 * @brief 打印任务信息
 */
void Task::printself() const
{
    const int width = 15;

    std::cout << std::left; // 左对齐

    Utils::setColor("31"); // Red
    std::cout << std::setw(width) << "Task ID:" << id << std::endl;

    Utils::setColor("32"); // Green
    std::cout << std::setw(width) << "Name:" << name << std::endl;

    Utils::setColor("33"); // Yellow
    std::cout << std::setw(width) << "Start Time:" << getStartTime() << std::endl;

    Utils::setColor("34"); // Blue
    std::cout << std::setw(width) << "Priority:" << priority << std::endl;

    Utils::setColor("35"); // Magenta
    std::cout << std::setw(width) << "Category:" << category << std::endl;

    Utils::setColor("36"); // Cyan
    std::cout << std::setw(width) << "Reminder Time:" << getReminderTime() << std::endl;

    Utils::resetColor(); // Reset to default color
    Utils::printSeparator();
}
