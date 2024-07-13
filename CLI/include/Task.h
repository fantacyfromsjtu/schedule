#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "TimeUtils.h"

/**
 * @brief 任务类，包含任务的各种属性
 */
class Task
{
public:
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
    Task(int id, const std::string &name, const std::string &startTime,
         const std::string &priority = "medium", const std::string &category = "other",
         const std::string &reminderTime = "", const bool &reminded = false);

    /**
     * @brief 获取任务ID
     * @return 返回任务ID
     */
    int getId() const { return id; }

    /**
     * @brief 获取任务名称
     * @return 返回任务名称
     */
    std::string getName() const { return name; }

    /**
     * @brief 获取任务开始时间
     * @return 返回任务开始时间
     */
    std::string getStartTime() const { return TimeUtils::formatTime(startTime); }

    /**
     * @brief 获取任务优先级
     * @return 返回任务优先级
     */
    std::string getPriority() const { return priority; }

    /**
     * @brief 获取任务分类
     * @return 返回任务分类
     */
    std::string getCategory() const { return category; }

    /**
     * @brief 获取提醒时间
     * @return 返回提醒时间
     */
    std::string getReminderTime() const { return TimeUtils::formatTime(reminderTime); }

    /**
     * @brief 获取任务是否已提醒
     * @return 返回任务是否已提醒
     */
    bool &getremind() { return reminded; }

    /**
     * @brief 获取任务是否已提醒（只读）
     * @return 返回任务是否已提醒
     */
    bool getremind_const() const { return reminded; }

    /**
     * @brief 打印任务信息
     */
    void printself() const;

private:
    int id;                                             ///< 任务ID
    std::string name;                                   ///< 任务名称
    std::chrono::system_clock::time_point startTime;    ///< 任务开始时间
    std::chrono::system_clock::time_point reminderTime; ///< 提醒时间
    std::string priority;                               ///< 任务优先级
    std::string category;                               ///< 任务分类
    bool reminded;                                      ///< 是否已经提醒
};

#endif // TASK_H
