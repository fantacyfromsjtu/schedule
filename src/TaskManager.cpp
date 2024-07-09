#include "TaskManager.h"
/**
 * @brief 添加任务
 * @param task 要添加的任务
 * @return 成功添加返回true，否则返回false
 */
bool TaskManager::addTask(const Task &task){
    return true;
}

/**
 * @brief 删除任务
 * @param id 要删除的任务ID
 * @return 成功删除返回true，否则返回false
 */
bool TaskManager::deleteTask(int id){
    return true;
}

/**
 * @brief 根据日期获取任务
 * @param date 日期（格式为YYYY-MM-DD）
 * @return 返回指定日期的任务列表
 */
std::vector<Task> TaskManager::getTasksByDate(const std::string &date) const{
    
}

/**
 * @brief 从文件加载任务
 * @param filename 文件名
 */
void TaskManager::loadTasks(const std::string &filename){

}

/**
 * @brief 保存任务到文件
 * @param filename 文件名
 */
void TaskManager::saveTasks(const std::string &filename) const{

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

bool TaskManager::isValidPriority(const std::string &priority){
    return true;
}

bool TaskManager::isValidCategory(const std::string &category){
    return true;
}

bool TaskManager::isUniqueTask(const Task &task) const{
    return true;
}
