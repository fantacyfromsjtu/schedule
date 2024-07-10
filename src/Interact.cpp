#include "Interact.h"
#include <limits>

void showHelp()
{
    std::cout << "\nUsage:\n";
    // 待完善
}

void ask_name_passwd(std::string &username, std::string &password)
{
    std::cout << "用户名:\n";
    std::cin >> username;
    std::cout << "密码:\n";
    std::cin >> password;
}

void ask_del(TaskManager &usermanager)
{
    std::cout << "输入要删除的任务id：\n";
    std::string input;
    std::cin >> input;
    int id = Utils::stringToInt(input);
    if (id == -1)
    {
        std::cerr << "非法id\n";
        return;
    }
    std::cout << "确认删除任务：" << id << " ?(y/n)";
    char yorn;
    std::cin >> yorn;
    if (yorn == 'y' || yorn == 'Y')
    {
        bool isdel = usermanager.deleteTask(id);
        if (!isdel)
        {
            std::cerr << "要删除的任务不存在！\n";
        }
    }
}

void ask_show(TaskManager &usermanager)
{
    std::string month;
    std::string day;
    std::cout << "查看任务的月份：(可以跳过，默认为当月)";
    std::getline(std::cin >> std::ws, month);
    std::cout << "查看任务的日期：(可以跳过，默认为当天)";
    std::getline(std::cin >> std::ws, day);
    if (!usermanager.showTask(month, day))
    {
        std::cout << "查看的时间段内无任务！\n";
    }
}

void ask_add(TaskManager &usermanager)
{
    std::cout << "新建任务的各属性（按空格默认跳过）\n";
    std::string name, startTime, priority, category, remindTime;

    std::cout << "任务名： \n";
    std::getline(std::cin >> std::ws, name);

    std::cout << "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）： \n";
    std::getline(std::cin >> std::ws, startTime);
    if (!usermanager.isValidStartTime(startTime))
    {
        std::cout << "启动时间非法！\n";
        return;
    }

    std::cout << "优先级（默认为medium）：\n";
    std::getline(std::cin >> std::ws, priority);
    if (priority.empty())
    {
        priority = "medium";
    }
    else if (!usermanager.isValidPriority(priority))
    {
        std::cout << "非法优先级！\n";
        return;
    }

    std::cout << "任务种类（默认为other）：\n";
    std::getline(std::cin >> std::ws, category);
    if (category.empty())
    {
        category = "other";
    }
    else if (!usermanager.isValidCategory(category))
    {
        std::cout << "非法种类！\n";
        return;
    }

    std::cout << "任务提醒时间（默认为空）：\n";
    std::getline(std::cin >> std::ws, remindTime);
    if (!remindTime.empty() && !usermanager.isValidRemindTime(remindTime, startTime))
    {
        std::cout << "提醒时间非法！\n";
        return;
    }

    int id = usermanager.getTasknum() + 1;
    Task newtask(id, name, startTime, priority, category, remindTime);
    if (usermanager.addTask(newtask))
    {
        std::cout << "添加任务 " << newtask.getName() << " 成功！\n";
    }
    else
    {
        std::cerr << "添加任务 " << newtask.getName() << " 失败\n";
    }
}
