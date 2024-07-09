#include "interact.h"

void showHelp()
{
    std::cout << "\nUsage:\n";
    // 待完善
}
void ask_name_passwd(std::string &username, std::string &password)
{
    std::cout << "用户名：\n";
    std::cin >> username;
    std::cout << "密码：\n ";
    std::cin >> password;
}

void ask_del(TaskManager &usermanager)
{
    std::cout << "输入要删除的任务id：\n";
    std::string input;
    std::cin >> input;
    int id = Utils::stringToInt(input);
    if(id == -1){
        std::cerr << "非法id\n";
        return;
    }
    std::cout << "确认删除任务：" << id << " ?(y/n)";
    char yorn;
    std::cin >> yorn;
    if (yorn == 'y' || yorn == 'Y'){
       bool isdel = usermanager.deleteTask(id);
       if(!isdel){
           std::cerr << "要删除的任务不存在！\n";
       }
    }
}

void ask_show(TaskManager &usermanager)
{
    std::string month;
    std::string day;
    std::cout << "查看任务的月份：(可以跳过，默认为当月)";
    std::cin >> month;
    std::cout << "查看任务的日期：(可以跳过，默认为当天)";
    std::cin >> day;
    if(!usermanager.showTask(month,day)){
        std::cout << "查看的时间段内无任务！\n";
    }
}

void ask_add(TaskManager &usermanager)
{
    std::cout << "新建任务的各属性（按空格默认跳过）\n";
    std::string name, startTime, priority, category, remindTime;
    std::cout << "任务名： \n";
    std::cin >> name;
    std::cout << "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）： \n";
    std::cin >> startTime; 

    //TODO:合法性检查：包括任务开始时间的格式，以及唯一性

    std::cout << "优先级（默认为medium）\n";
    std::cin >> priority;
    if(!usermanager.isValidPriority(priority)){
        std::cout << "非法优先级！\n";
        return;
    }
    std::cout << "任务种类（默认为other）\n";
    std::cin >> category;
    if (!usermanager.isValidCategory(category))
    {
        std::cout << "非法种类！\n";
        return;
    }
    std::cout << "任务提醒时间（默认为空）\n";
    std::cin >> remindTime;
    
    //TODO:合法性检查：包括时间格式，提醒时间是否在任务启动时间之前等等

    // TODO: 按照目前该用户的任务id序列分配一个id （升序）
    int id = usermanager.getTasknum() + 1;
    Task newtask(id, name, startTime, priority, category, remindTime);
}