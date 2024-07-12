// 包含一些与用户交互的函数
#ifndef INTERACT_H
#define INTERACT_H

#include<iostream>
#include "TaskManager.h"
#include "Utils.h"
#include "Task.h"

void showHelp(); // 打印帮助

void ask_name_passwd(std::string &username, std::string &password);

void ask_del(TaskManager &usermanager);

void ask_show(TaskManager &usermanager);

void ask_add(TaskManager &usermanager);

void ask_modifypassword(User &user);

#endif