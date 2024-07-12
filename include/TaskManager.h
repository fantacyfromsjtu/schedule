#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <mutex>
class User; // 前向声明
/**
 * @brief 任务管理类，管理任务的添加、删除、显示等操作
 */
class TaskManager
{
public:
    TaskManager(std::string username);

    int getTasknum() const { return tasks.size(); }

    std::string getTaskfile() const
    {
        return this->taskfile;
    }

    std::vector<Task>& getTasks()
    {
        return tasks;
    }

    /**
     * @brief 添加任务
     * @param task 要添加的任务
     * @return 成功添加返回true，否则返回false
     */
    bool addTask(const Task &task);

    /**
     * @brief 删除任务
     * @param id 要删除的任务ID
     * @return 成功删除返回true，否则返回false
     */
    bool deleteTask(int id);


    /**
     * @brief 从文件加载任务
     * @param filename 文件名
     */
    void loadTasks(const std::string &filename);

    /**
     * @brief 保存任务到文件
     * @param filename 文件名
     */
    bool saveTasks(const Task &task,const std::string &filename) const;

    /**
     * @brief 显示任务
     * @param month 月份（格式为YYYY-MM，缺省则为当前月份）
     * @param day 日期（格式为YYYY-MM-DD，缺省则为当前日期）
     */
    bool showTask(const std::string &month = "", const std::string &day = "");

    bool isValidPriority(const std::string &priority);

    bool isValidCategory(const std::string &category);

    bool isValidStartTime(const std::string &startTime);

    bool isValidRemindTime(const std::string &remindTime, const std::string &startTime);
   

private:
    std::string taskfile; //该任务管理器对应的文件名
    std::vector<Task> tasks; ///< 任务列表
    std::unordered_set<std::string> prioritySet ;
    std::unordered_set<std::string> categorySet;
    
    void sort_by_startTime();
};

#endif // TASKMANAGER_H
