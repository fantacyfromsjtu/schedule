#include "Interact.h"
#include "Utils.h"
#include "User.h"
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <limits>

void showHelp()
{
    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("Usage:\n");
    Utils::resetColor();
    std::cout << "  myschedule <command>\n";

    Utils::setColor("36"); // Cyan
    Utils::printBold("Commands:\n");
    Utils::resetColor();
    std::cout << "  run        - 启动日程管理系统\n";
    std::cout << "  -h         - 显示帮助信息\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("在启动日程管理系统后，可用的命令有:\n");
    Utils::resetColor();
    std::cout << "  addtask    - 添加任务\n";
    std::cout << "  deltask    - 删除任务\n";
    std::cout << "  showtask   - 显示任务\n";
    std::cout << "  q          - 退出系统\n";
    std::cout << "  modifypassword - 修改密码\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("命令示例:\n");
    Utils::resetColor();
    std::cout << "  myschedule run                - 启动日程管理系统\n";
    std::cout << "  addtask                       - 添加一个新任务\n";
    std::cout << "  deltask                       - 删除一个任务\n";
    std::cout << "  showtask                      - 显示任务\n";
    std::cout << "  q                             - 退出系统\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("在系统启动后:\n");
    Utils::resetColor();
    std::cout << "  注册或登录后，您可以添加、删除或显示任务。\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("添加任务的详细步骤:\n");
    Utils::resetColor();
    std::cout << "  1. 输入任务名称。\n";
    std::cout << "  2. 输入任务开始时间（格式为YYYY-MM-DD HH:MM:SS）。\n";
    std::cout << "  3. 输入任务优先级（按回车默认medium）。\n";
    std::cout << "  4. 输入任务种类（按回车默认other）。\n";
    std::cout << "  5. 输入任务提醒时间（按回车默认为任务开始时间）。\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("删除任务的详细步骤:\n");
    Utils::resetColor();
    std::cout << "  1. 输入要删除的任务ID。\n";
    std::cout << "  2. 确认是否删除任务（y/n）。\n";

    Utils::printSeparator();
    Utils::setColor("36"); // Cyan
    Utils::printBold("显示任务的详细步骤:\n");
    Utils::resetColor();
    std::cout << "  1. 输入要查看任务的月份（按回车默认当月）。\n";
    std::cout << "  2. 输入要查看任务的日期（按回车默认显示当月所有天）。\n";
    Utils::printSeparator();
}

void cinpasswd(std::string &password)
{
    // 禁用回显
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cin >> password;

    // 恢复回显
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void ask_name_passwd(std::string &username, std::string &password)
{
    std::cout << "用户名:\n";
    std::cin >> username;
    std::cout << "密码:\n";
    cinpasswd(password);
    std::cout << std::endl; // 换行
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
        std::lock_guard<std::mutex> lock(Utils::mtx); // 加锁
        bool isdel = usermanager.deleteTask(id);
        if (!isdel)
        {
            std::cerr << "要删除的任务不存在！\n";
        }
        else
        {
            std::cout << "删除ID为:" << id << "的任务成功！\n";
        }
    }
}

void ask_show(TaskManager &usermanager)
{
    std::string month;
    std::string day;

    // 清除输入缓冲区
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "查看任务的月份(格式：两位数字)：(可以跳过，默认为当月)";
    std::getline(std::cin, month);
    std::cout << "查看任务的日期(格式：两位数字)：(可以跳过，默认显示每一天)";
    std::getline(std::cin, day);
    std::lock_guard<std::mutex> lock(Utils::mtx); // 加锁
    if (!usermanager.showTask(month, day))
    {
        std::cout << "查看的时间段内无任务！\n";
    }
}

void ask_add(TaskManager &usermanager)
{
    std::cout << "新建任务的各属性（按回车默认跳过）\n";
    std::string name, startTime, priority, category, remindTime;

    // 清除输入缓冲区
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "任务名：\n";
    std::getline(std::cin, name);

    std::cout << "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）：\n";
    std::getline(std::cin, startTime);
    if (!usermanager.isValidStartTime(startTime))
    {
        std::cout << "启动时间非法！\n";
        return;
    }

    std::cout << "优先级（默认为medium）：\n";
    std::getline(std::cin, priority);
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
    std::getline(std::cin, category);
    if (category.empty())
    {
        category = "other";
    }
    else if (!usermanager.isValidCategory(category))
    {
        std::cout << "非法种类！\n";
        return;
    }

    std::cout << "任务提醒时间（默认为任务开始时间）：\n";
    std::getline(std::cin, remindTime);
    if (!remindTime.empty() && !usermanager.isValidRemindTime(remindTime, startTime))
    {
        std::cout << "提醒时间非法！\n";
        return;
    }

    int id = usermanager.getNewId();
    Task newtask(id, name, startTime, priority, category, remindTime);
    std::lock_guard<std::mutex> lock(Utils::mtx); // 加锁
    if (usermanager.addTask(newtask))
    {
        std::cout << "添加任务 " << newtask.getName() << " 成功！\n";
    }
    else
    {
        std::cerr << "添加任务 " << newtask.getName() << " 失败\n";
    }
}
void ask_modifypassword(User &user)
{
    std::cout << "修改密码界面\n";
    std::cout << "原密码：\n";
    std::string oldpasswd;
    cinpasswd(oldpasswd);
    if (Utils::sha256(oldpasswd) != user.getPasswordHash())
    {
        std::cout << "原密码错误！\n";
        return;
    }
    std::cout << "请输入新密码：\n";
    std::string newpasswd;
    cinpasswd(newpasswd);
    if (user.modifyPassword(newpasswd))
    {
        std::cout << "修改密码成功！\n";
    }
    else
    {
        std::cerr << "修改密码失败！\n";
    }
}