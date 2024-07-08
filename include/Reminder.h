#ifndef REMINDER_H
#define REMINDER_H

#include "TaskManager.h"
#include <thread>
#include <atomic>

/**
 * @brief 提醒类，负责处理任务提醒功能
 */
class Reminder
{
public:
    /**
     * @brief 构造函数
     * @param taskManager 任务管理对象
     */
    Reminder(TaskManager &taskManager);

    /**
     * @brief 启动提醒
     */
    void start();

    /**
     * @brief 停止提醒
     */
    void stop();

private:
    /**
     * @brief 提醒循环
     */
    void reminderLoop();

    TaskManager &taskManager;   ///< 任务管理对象
    std::atomic<bool> running;  ///< 运行标志
    std::thread reminderThread; ///< 提醒线程
};

#endif // REMINDER_H
