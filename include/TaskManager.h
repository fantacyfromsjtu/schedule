#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <string>
#include <unordered_set>

/**
 * @brief 任务管理类，管理任务的添加、删除、显示等操作
 */
class TaskManager
{
public:
    int getTasknum(){
        return task_num;
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
     * @brief 根据日期获取任务
     * @param date 日期（格式为YYYY-MM-DD）
     * @return 返回指定日期的任务列表
     */
    std::vector<Task> getTasksByDate(const std::string &date) const;

    /**
     * @brief 从文件加载任务
     * @param filename 文件名
     */
    void loadTasks(const std::string &filename);

    /**
     * @brief 保存任务到文件
     * @param filename 文件名
     */
    void saveTasks(const std::string &filename) const;

    /**
     * @brief 显示任务
     * @param month 月份（格式为YYYY-MM，缺省则为当前月份）
     * @param day 日期（格式为YYYY-MM-DD，缺省则为当前日期）
     */
    bool showTask(const std::string &month = "", const std::string &day = "") const;

    bool isValidPriority(const std::string &priority);

    bool isValidCategory(const std::string &category);

private:
    std::vector<Task> tasks; ///< 任务列表

    /**
     * @brief 检查任务是否唯一
     * @param task 要检查的任务
     * @return 唯一则返回true，否则返回false
     */
    bool isUniqueTask(const Task &task) const;

    std::unordered_set<std::string> prioritySet = {"high","medium","low"};
    std::unordered_set<std::string> categorySet = {"study","life","other"};

    int task_num = 0;
};

#endif // TASKMANAGER_H
