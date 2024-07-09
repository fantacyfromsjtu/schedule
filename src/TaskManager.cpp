#include "TaskManager.h"
#include <iostream>
#include <algorithm>
// 构造函数

TaskManager::TaskManager(std::string username)
{
    this->taskfile = Utils::getTaskFile(username);
    this->prioritySet = {"high",
                         "medium",
                         "low"};
    this->categorySet = {"study",
                         "life",
                         "other"};
    this->tasks = std::vector<Task>();
    loadTasks(taskfile);
}
/**
 * @brief 添加任务
 * @param task 要添加的任务
 * @return 成功添加返回true，否则返回false
 */
bool TaskManager::addTask(const Task &task)
{
    tasks.push_back(task);
    if (saveTasks(task, taskfile))
        return true;
    else
        return false;
}

/**
 * @brief 删除任务
 * @param id 要删除的任务ID
 * @return 成功删除返回true，否则返回false
 */
bool TaskManager::deleteTask(int id)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task &task)
                           { return task.getId() == id; });
    if(it == tasks.end())
        return false;

    tasks.erase(it); //删除该任务
    // 更新文件
    //  读取文件内容
    std::ifstream fileIn(taskfile);
    if (!fileIn)
    {
        std::cerr << "Unable to open file: " << taskfile << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fileIn, line))
    {
        std::istringstream iss(line);
        int fileId;
        if (iss >> fileId && fileId == id)
        {
            continue; // 跳过要删除的行
        }
        lines.push_back(line);
    }
    fileIn.close();

    // 将更新后的内容写回文件
    std::ofstream fileOut(taskfile);
    if (!fileOut)
    {
        std::cerr << "Unable to open file for writing: " << taskfile << std::endl;
        return;
    }

    for (const auto &l : lines)
    {
        fileOut << l << std::endl;
    }
    fileOut.close();
}

/**
 * @brief 根据日期获取任务
 * @param date 日期（格式为YYYY-MM-DD）
 * @return 返回指定日期的任务列表
 */
std::vector<Task> TaskManager::getTasksByDate(const std::string &date) const
{
}

/**
 * @brief 从文件加载任务
 * @param filename 文件名
 */
void TaskManager::loadTasks(const std::string &filename)
{
    int id;                                             
    std::string name;                                   
    std::string startTime;    
    std::string priority;                               
    std::string category;
    std::string reminderTime;
    std::ifstream taskfile(filename);
    if (!taskfile) // 打开失败
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    while (taskfile >> id >> name >> startTime >> priority >> category >> reminderTime)
    {
        Task task(id, name, startTime, priority, category, reminderTime);
        tasks.push_back(task);
    }
}

/**
 * @brief 保存单个任务到文件，每个文件格式："id name starttime priority category remindtime"
 * @param filename 文件名
 */
bool TaskManager::saveTasks(const Task &task, const std::string &filename) const
{
    std::ofstream taskFile(filename, std::ios::app);
    if (taskFile.is_open())
    {
        taskFile << task.getId() << " " << task.getName() << " " << task.getStartTime() << " "
                 << task.getPriority() << " " << task.getCategory() << task.getReminderTime();
        taskFile.close();
    }
    else
    {
        std::cerr << "Failed to save the task " << task.getName() << "!\n";
        return false;
    }
    return true;
}

/**
 * @brief 显示任务
 * @param month 月份（格式为YYYY-MM，缺省则为当前月份）
 * @param day 日期（格式为YYYY-MM-DD，缺省则为当前日期）
 */
bool TaskManager::showTask(const std::string &month = "", const std::string &day = "") const
{
    return true;
}

bool TaskManager::isValidPriority(const std::string &priority)
{
    return true;
}

bool TaskManager::isValidCategory(const std::string &category)
{
    return true;
}

bool TaskManager::isValidStartTime(const std::string &startTime)
{
}

bool TaskManager::isValidRemindTime(const std::string &remindTime)
{
}
