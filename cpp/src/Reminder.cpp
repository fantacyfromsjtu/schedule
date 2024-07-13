#include "Reminder.h"
#include "Utils.h"
#include <iostream>
#include <ctime>

/**
 * @brief 构造函数
 * @param taskManager 任务管理器的引用
 */
Reminder::Reminder(TaskManager &taskManager)
    : taskManager(taskManager), running(false) {}

/**
 * @brief 开始提醒检查循环
 */
void Reminder::start()
{
    running = true;
    reminderThread = std::thread([this]()
                                 {
        while (running) {
            checkReminders();
            std::this_thread::sleep_for(std::chrono::seconds(10)); // 每10s检查一次
        } });
}

/**
 * @brief 停止提醒检查循环
 */
void Reminder::stop()
{
    running = false;
    if (reminderThread.joinable())
    {
        reminderThread.join();
    }
}

/**
 * @brief 检查任务是否需要提醒
 */
void Reminder::checkReminders()
{
    auto now = TimeUtils::parseTime(TimeUtils::getCurrentTime());
    std::lock_guard<std::mutex> lock(Utils::mtx); // 获取锁，保护任务列表
    for (auto &task : taskManager.getTasks())
    {
        auto remindTime = TimeUtils::parseTime(task.getReminderTime());
        auto startTime = TimeUtils::parseTime(task.getStartTime());

        if (!task.getremind() && remindTime <= now && remindTime <= startTime && now + std::chrono::seconds(2) > remindTime) // 2s 提前量
        {
            task.getremind() = true;
            taskManager.deleteTask(task.getId());
            taskManager.addTask(task);
            Utils::setColor("1"); // Bold
            std::cout << "\nREMIND!!\n";
            Utils::resetColor();
            task.printself();
            Utils::setColor("1"); // Bold
            std::cout << "IS TO START SOON!\n";
            Utils::resetColor();
        }
    }
}
