#include "Reminder.h"
#include <iostream>
#include <ctime>

Reminder::Reminder(TaskManager &taskManager)
    : taskManager(taskManager), running(false) {}

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

void Reminder::stop()
{
    running = false;
    if (reminderThread.joinable())
    {
        reminderThread.join();
    }
}

void Reminder::checkReminders()
{
    auto now = TimeUtils::parseTime(TimeUtils::getCurrentTime());
    for (auto &task : taskManager.getTasks())
    {
        auto remindTime = TimeUtils::parseTime(task.getReminderTime());
        auto startTime = TimeUtils::parseTime(task.getStartTime());
        if (!task.reminded&&remindTime <= now && remindTime <= startTime && now + std::chrono::seconds(10) > remindTime) //10s 提前量
        {
            task.reminded = true;
            std::cout << "REMIND!!\n";
            task.printself();
            std::cout << "IS TO START SOON!\n";
        }
    }
}
