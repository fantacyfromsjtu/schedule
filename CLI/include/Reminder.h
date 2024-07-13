#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include "Task.h"
#include "TaskManager.h"
#include "TimeUtils.h"

/**
 * @brief 提醒类，处理任务的提醒功能
 */
class Reminder
{
public:
    /**
     * @brief 构造函数
     * @param taskManager 任务管理器的引用
     */
    Reminder(TaskManager &taskManager);

    /**
     * @brief 开始提醒检查循环
     */
    void start();

    /**
     * @brief 停止提醒检查循环
     */
    void stop();

private:
    TaskManager &taskManager;   ///< 任务管理器的引用
    std::atomic<bool> running;  ///< 控制线程运行的标志
    std::thread reminderThread; ///< 提醒线程

    /**
     * @brief 检查任务是否需要提醒
     */
    void checkReminders();
};

#endif // REMINDER_H
