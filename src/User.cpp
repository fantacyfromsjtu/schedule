#include "User.h"
#include <fstream>
#include <map>
#include <iostream>

//构造函数
User::User(const std::string &username, const std::string &passwordHash)
    : username(username), passwordHash(passwordHash), manager(username)
{}

const std::string usersfile = "../data/users.txt";
// 读取用户文件并存储用户名和哈希值
std::map<std::string, std::string>
readUsers(const std::string &filename)
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
bool User::registeR()
{
    // 读取现有用户
    std::map<std::string, std::string> users = readUsers(usersfile);
    // 检查用户名是否存在
    if (users.find(this->username) != users.end())
    {
        return false;
    }
    // 是新用户，则更新users.txt，并且新建task/<username>_task_task.txt
    std::ofstream file(usersfile, std::ios::app);
    file << this->username << " " << this->passwordHash << std::endl;
    std::string taskFilename =Utils::getTaskFile(username);
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

bool User::login(const std::string &username, const std::string &passwordHash)
{
    std::map<std::string, std::string> users = readUsers(usersfile);
    if (users.find(username) == users.end() || users[username] != passwordHash)
    {
        //用户名不存在或者密码错误
        return false;
    }
    return true;
}
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