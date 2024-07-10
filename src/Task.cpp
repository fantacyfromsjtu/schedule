#include "Task.h"
/**
 * @brief 构造函数，初始化任务属性
 * @param id 任务ID
 * @param name 任务名称
 * @param startTime 任务开始时间（格式为YYYY-MM-DD HH:MM:SS）
 * @param priority 任务优先级（默认中等）
 * @param category 任务分类（默认一般）
 * @param reminderTime 提醒时间（格式为YYYY-MM-DD HH:MM:SS）
 */
Task::Task(int id, const std::string &name, const std::string &startTime,
           const std::string &priority, const std::string &category,
           const std::string &reminderTime)
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
    else{
        this->reminderTime = this->startTime;
    }
}

void Task::printself() const
{
    // 定义每列的宽度
    const int width = 15;

    std::cout << std::left; // 左对齐
    std::cout << std::setw(width) << "Task ID:" << id << std::endl;
    std::cout << std::setw(width) << "Name:" << name << std::endl;
    std::cout << std::setw(width) << "Start Time:" << getStartTime() << std::endl;
    std::cout << std::setw(width) << "Priority:" << priority << std::endl;
    std::cout << std::setw(width) << "Category:" << category << std::endl;
    std::cout << std::setw(width) << "Reminder Time:" << getReminderTime() << std::endl;
}