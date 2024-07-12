// User.cpp
// 用户类实现文件，包含用户名、密码散列和任务管理器的相关操作

#include "User.h"
#include <fstream>
#include <map>
#include <iostream>

// 构造函数，初始化用户名和任务管理器
User::User(const std::string &username, const std::string &passwordHash)
    : username(username), passwordHash(passwordHash), manager(username)
{
}

// 用户数据文件路径
const std::string usersfile = "../data/users.txt";

// 读取用户文件并存储用户名和哈希值
std::map<std::string, std::string> readUsers(const std::string &filename)
{
    std::map<std::string, std::string> users;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string username, hash;
        if (iss >> username >> hash)
        {
            users[username] = hash;
        }
    }
    return users;
}

// 注册函数，检查用户名是否存在，如果不存在则添加新用户并创建任务文件
bool User::registeR()
{
    // 读取现有用户
    std::map<std::string, std::string> users = readUsers(usersfile);

    // 检查用户名是否存在
    if (users.find(this->username) != users.end())
    {
        return false;
    }

    // 添加新用户到users.txt
    std::ofstream file(usersfile, std::ios::app);
    file << this->username << " " << this->passwordHash << std::endl;

    // 创建任务文件
    std::string taskFilename = Utils::getTaskFile(username);
    std::ofstream taskFile(taskFilename);
    if (taskFile.is_open())
    {
        taskFile.close();
    }
    else
    {
        std::cerr << "Failed to create task file for user " << username << "." << std::endl;
        return false;
    }

    return true;
}

// 登录函数，检查用户名是否存在且密码是否正确
bool User::login(const std::string &username, const std::string &passwordHash)
{
    std::map<std::string, std::string> users = readUsers(usersfile);

    // 检查用户名和密码
    if (users.find(username) == users.end() || users[username] != passwordHash)
    {
        return false;
    }

    return true;
}

// 修改密码函数，更新内存和文件中的密码散列
bool User::modifyPassword(const std::string &newPasswd)
{
    std::map<std::string, std::string> users = readUsers(usersfile);

    // 检查用户名是否存在
    if (users.find(this->username) == users.end())
    {
        return false;
    }

    // 更新内存中的密码散列
    this->passwordHash = Utils::sha256(newPasswd);

    // 更新文件中的密码散列
    std::ofstream file(usersfile);
    if (!file)
    {
        std::cerr << "Error opening file: " << usersfile << std::endl;
        return false;
    }

    for (const auto &user : users)
    {
        if (user.first == this->username)
        {
            file << this->username << " " << this->passwordHash << std::endl;
        }
        else
        {
            file << user.first << " " << user.second << std::endl;
        }
    }

    file.close();
    return true;
}
