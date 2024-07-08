// 主程序入口
#include <iostream>
#include <string>
#include <algorithm>
#include "TaskManager.h"
#include "User.h"
#include "Utils.h"
void showHelp() // 打印帮助
{
    std::cout << "\nUsage:\n";
}

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
        // 让用户选择注册或者登录
        std::string username;
        std::string password;
        bool islogin = false; // 是否在登录状态，初始未登录
        while (!islogin)
        {
            std::cout
                << "注册（输入r） or 登录（输入l） or 退出（输入q）\n";
            char input;
            std::cin >> input;
            switch (input)
            {
            case 'r':
            { // 注册
                while (1)
                {
                    std::cout << "注册界面\n";
                    std::cout << "用户名：\n";
                    std::cin >> username;
                    std::cout << "密码：\n ";
                    std::cin >> password;
                    User new_user(username, User::hashPassword(password));
                    if (new_user.registeR())
                    {
                        std::cout << "注册成功！\n";
                        break;
                    }
                    else
                    {
                        std::cout << "用户名重复力，重新输入罢\n";
                    }
                }
                break;
            }
            case 'l':
            { // 登录
                std::cout << "登录界面\n";
                std::cout << "用户名：\n";
                std::cin >> username;
                std::cout << "密码：\n ";
                std::cin >> password;
                if (User::login(username, User::hashPassword(password)))
                {
                    std::cout << "登录成功！\n";
                    // 跳转出去
                    islogin = true;
                    break;
                }
                else
                {
                    std::cout << "用户名或密码错误！\n";
                }

                break;
            }
            case 'q':
                // 退出
                std::cout << "日志系统，关闭！\n";
                return 0;

            default:
                // 出错
                std::cerr << "Invalid input!\n";
            }
        } // end of while

        // 此时已经在登录状态,创建一个用户对象
        User user(username, User::hashPassword(password));
        // 加载任务
        std::cout << "任务加载中！\n";
        TaskManager user_manager = user.getTaskManager();
        std::string filename = "../data/tasks/" + username + "_task.txt";
        user_manager.loadTasks(filename);
        std::cout << "任务加载成功！\n";

        // 进行主程序
        while (true)
        {
            std::cout << "请输入命令：";
            std::string command;
            std::cin >> command;
            transform(command.begin(), command.end(), command.begin(), ::tolower); // 转小写
            std::vector<std::string> parsed_cmd = Utils::split(command, ' ');      // 分割命令

            if (command == "-h")
            {
                showHelp();
            }
            else if (parsed_cmd[0] == "deltask" && parsed_cmd.size() == 2)
            {
                int del_id = Utils::stringToInt(parsed_cmd[1]);
                user_manager.deleteTask(del_id);
            }
            else if (parsed_cmd[0] == "showtask")
            {
                switch (parsed_cmd.size())
                {
                case 1:
                    user_manager.showTask();
                    break;
                case 2:
                    user_manager.showTask(parsed_cmd[1]);
                    break;
                case 3:
                    user_manager.showTask(parsed_cmd[1], parsed_cmd[2]);
                default:
                    std::cerr << "wrong number of args!\n";
                    showHelp();
                }
            }
            else if (parsed_cmd[0] == "addtask")
            {
                /* 等待用户输入具体任务 */
            }
            
            
        }
    }