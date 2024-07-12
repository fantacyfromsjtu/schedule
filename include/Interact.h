// Interact.h

#ifndef INTERACT_H
#define INTERACT_H

#include <iostream>
#include "TaskManager.h"
#include "Utils.h"
#include "Task.h"

/**
 * @brief 显示帮助信息
 */
void showHelp();

/**
 * @brief 询问用户名和密码
 * @param username 用于存储输入的用户名
 * @param password 用于存储输入的密码
 */
void ask_name_passwd(std::string &username, std::string &password);

/**
 * @brief 询问并删除任务
 * @param usermanager 任务管理器对象
 */
void ask_del(TaskManager &usermanager);

/**
 * @brief 询问并显示任务
 * @param usermanager 任务管理器对象
 */
void ask_show(TaskManager &usermanager);

/**
 * @brief 询问并添加任务
 * @param usermanager 任务管理器对象
 */
void ask_add(TaskManager &usermanager);

/**
 * @brief 询问并修改用户密码
 * @param user 用户对象
 */
void ask_modifypassword(User &user);

#endif // INTERACT_H
