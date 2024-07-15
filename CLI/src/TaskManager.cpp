#include "TaskManager.h"
#include <iostream>
#include <algorithm>

// 构造函数
TaskManager::TaskManager(std::string username)
{
    this->taskfile = Utils::getTaskFile(username);
    this->prioritySet = {"high", "medium", "low"};
    this->categorySet = {"study", "work", "life", "other"};
    this->tasks = std::vector<Task>();
}

/**
 * @brief 获取新任务ID
 * @return 返回新的任务ID
 */
int TaskManager::getNewId() const
{
    int maxid = 0;
    for (const auto &task : tasks)
    {
        if (task.getId() > maxid)
        {
            maxid = task.getId();
        }
    }
    return maxid + 1;
}

/**
 * @brief 添加任务
 * @param task 要添加的任务
 * @return 成功添加返回true，否则返回false
 */
bool TaskManager::addTask(const Task &task)
{
    tasks.push_back(task);
    return saveTasks(task, taskfile);
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
    if (it == tasks.end())
        return false;

    tasks.erase(it); // 删除该任务

    // 读取文件内容
    std::ifstream fileIn(taskfile);
    if (!fileIn)
    {
        std::cerr << "Unable to open file: " << taskfile << std::endl;
        return false;
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
        return false;
    }

    for (const auto &l : lines)
    {
        fileOut << l << std::endl;
    }
    fileOut.close();
    return true;
}

/**
 * @brief 从文件加载任务
 * @param filename 文件名
 */
void TaskManager::loadTasks(const std::string &filename)
{
    std::ifstream taskfile(filename);
    if (!taskfile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(taskfile, line))
    {
        std::istringstream iss(line);
        int id;
        std::string name;
        std::string startTime;
        std::string priority;
        std::string category;
        std::string reminderTime;
        bool reminded = false;

        if (!(iss >> id >> name >> std::ws))
        {
            std::cerr << "Error reading task ID and name: " << line << std::endl;
            continue;
        }

        std::getline(iss, startTime, '"');
        std::getline(iss, startTime, '"');
        iss >> std::ws >> priority >> category;
        std::getline(iss, reminderTime, '"');
        std::getline(iss, reminderTime, '"');

        if (iss.fail())
        {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
        
        Task task(id, name, startTime, priority, category, reminderTime, reminded);
        tasks.push_back(task);
    }
}

/**
 * @brief 保存单个任务到文件，每个文件格式："id name starttime priority category remindtime reminded"
 * @param filename 文件名
 */
bool TaskManager::saveTasks(const Task &task, const std::string &filename) const
{
    std::ofstream taskFile(filename, std::ios::app);
    if (taskFile.is_open())
    {
        taskFile << task.getId() << " " << task.getName() << " \"" << task.getStartTime() << "\" "
                 << task.getPriority() << " " << task.getCategory() << " \"" << task.getReminderTime() << "\" "
                  << std::endl;
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
bool TaskManager::showTask(const std::string &month, const std::string &day)
{
    sort_by_startTime();
    std::string targetmonth;
    std::string targetdate;
    if (month.empty())
    {
        targetmonth = TimeUtils::getCurrentMonth();
    }
    else
    {
        targetmonth = TimeUtils::getCurrentYear() + "-" + month;
        if (!TimeUtils::isValidDate(targetmonth + "-01"))
        {
            std::cerr << "输入月份非法！\n";
            return false;
        }
    }
    if (day.empty())
    {
        targetdate = TimeUtils::getCurrentDate();
    }
    else
    {
        targetdate = TimeUtils::getCurrentMonth() + "-" + day;
        if (!TimeUtils::isValidDate(targetdate))
        {
            std::cerr << "输入日期非法！\n";
            return false;
        }
    }
    bool found = false;
    for (const auto &task : tasks)
    {
        std::string taskDate = task.getStartTime().substr(0, 10); // starttime格式为YYYY-MM-DD HH:MM:SS
        std::string taskMonth = task.getStartTime().substr(0, 7);
        if (!day.empty() && taskDate == targetdate)
        {
            // 显示具体日期的任务
            task.printself();
            found = true;
        }
        else if (day.empty() && taskMonth == targetmonth)
        {
            // 显示整个月份的任务
            task.printself();
            found = true;
        }
    }
    return found;
}

/**
 * @brief 验证优先级是否合法
 * @param priority 优先级
 * @return 合法返回true，否则返回false
 */
bool TaskManager::isValidPriority(const std::string &priority)
{
    return this->prioritySet.count(priority) != 0;
}

/**
 * @brief 验证任务分类是否合法
 * @param category 分类
 * @return 合法返回true，否则返回false
 */
bool TaskManager::isValidCategory(const std::string &category)
{
    return this->categorySet.count(category) != 0;
}

/**
 * @brief 验证任务开始时间是否合法且唯一
 * @param startTime 开始时间
 * @return 合法且唯一返回true，否则返回false
 */
bool TaskManager::isValidStartTime(const std::string &startTime)
{
    // 先检查时间格式和是否在当前时间之后
    if (!TimeUtils::isValidTime(startTime) ||
        TimeUtils::parseTime(TimeUtils::getCurrentTime()) >= TimeUtils::parseTime(startTime))
    {
        return false;
    }

    // 检查启动时间是否唯一
    auto newStartTime = TimeUtils::parseTime(startTime);
    for (const auto &task : tasks)
    {
        if (TimeUtils::parseTime(task.getStartTime()) == newStartTime)
        {
            return false; // 存在相同启动时间的任务
        }
    }

    return true;
}

/**
 * @brief 验证提醒时间是否合法
 * @param remindTime 提醒时间
 * @param startTime 开始时间
 * @return 合法返回true，否则返回false
 */
bool TaskManager::isValidRemindTime(const std::string &remindTime, const std::string &startTime)
{
    if (TimeUtils::isValidTime(remindTime) &&
        TimeUtils::parseTime(remindTime) <= TimeUtils::parseTime(startTime))
    {
        return true;
    }
    return false;
}

/**
 * @brief 按开始时间排序任务
 */
void TaskManager::sort_by_startTime()
{
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
              { return TimeUtils::parseTime(a.getStartTime()) < TimeUtils::parseTime(b.getStartTime()); });
}
