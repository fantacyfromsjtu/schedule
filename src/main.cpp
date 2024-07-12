// main.cpp
#include <iostream>
#include <string>
#include <algorithm>
#include "TaskManager.h"
#include "User.h"
#include "Utils.h"
#include "Interact.h"
#include "Reminder.h"
#include "TimeUtils.h"

void handleUserRegistration(std::string &username, std::string &password);
bool handleUserLogin(std::string &username, std::string &password);
void mainLoop(User &user);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Invalid number of args!\n";
        showHelp();
        return 1;
    }

    std::string arg = argv[1];
    if (arg == "-h")
    {
        showHelp();
        return 1;
    }
    else if (arg == "run")
    {
        std::cout << "日志系统，启动！\n";

        std::string username;
        std::string password;
        bool islogin = false;

        while (!islogin)
        {
            std::cout << "注册（输入r） or 登录（输入l） or 退出（输入q）\n";
            char input;
            std::cin >> input;
            switch (input)
            {
            case 'r':
                handleUserRegistration(username, password);
                break;
            case 'l':
                islogin = handleUserLogin(username, password);
                break;
            case 'q':
                std::cout << "日志系统，关闭！\n";
                return 0;
            default:
                std::cerr << "Invalid input!\n";
            }
        }

        User user(username, User::hashPassword(password));
        mainLoop(user);
    }
    else
    {
        std::cerr << "Invalid argument！\n";
    }
}

void handleUserRegistration(std::string &username, std::string &password)
{
    while (true)
    {
        std::cout << "注册界面\n";
        ask_name_passwd(username, password);
        User new_user(username, User::hashPassword(password));
        if (new_user.registeR())
        {
            std::cout << "注册成功！\n";
            break;
        }
        else
        {
            std::cout << "用户名重复，请重新输入。\n";
        }
    }
}

bool handleUserLogin(std::string &username, std::string &password)
{
    std::cout << "登录界面\n";
    ask_name_passwd(username, password);
    if (User::login(username, User::hashPassword(password)))
    {
        std::cout << "登录成功！\n";
        return true;
    }
    else
    {
        std::cout << "用户名或密码错误！\n";
        return false;
    }
}

void mainLoop(User &user)
{
    TaskManager &user_manager = user.manager;
    std::string filename = "../data/tasks/" + user.getUsername() + "_task.txt";
    user_manager.loadTasks(filename);
    std::cout << "任务加载成功！\n";

    Reminder reminder(user_manager);
    reminder.start();

    while (true)
    {
        std::cout << "请输入命令：";
        std::string command;
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (command == "-h")
        {
            showHelp();
        }
        else if (command == "deltask")
        {
            ask_del(user_manager);
        }
        else if (command == "showtask")
        {
            ask_show(user_manager);
        }
        else if (command == "addtask")
        {
            ask_add(user_manager);
        }
        else if (command == "modifypassword"){
            ask_modifypassword(user);
        }
        else if (command == "q")
        {
            std::cout << "日志系统，关闭！\n";
            break;
        }
        else
        {
            std::cerr << "Invalid cmd!\n";
            showHelp();
        }
    }

    reminder.stop();
}
