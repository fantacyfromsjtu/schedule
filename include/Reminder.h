#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include "Task.h"
#include "TaskManager.h"
#include "TimeUtils.h"

class Reminder
{
public:
    /**
     * @brief 构造函数
     * @param taskManager 任务管理器的引用
     */
    Reminder(const TaskManager &taskManager);

    /**
     * @brief 开始提醒检查循环
     */
    void start();

    /**
     * @brief 停止提醒检查循环
     */
    void stop();

private:
    const TaskManager &taskManager; ///< 任务管理器的引用
    std::atomic<bool> running;      ///< 控制线程运行的标志
    std::thread reminderThread;     ///< 提醒线程

    /**
     * @brief 检查任务是否需要提醒
     */
    void checkReminders();
};

#endif // REMINDER_H
