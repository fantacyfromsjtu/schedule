#ifndef USER_H
#define USER_H

#include <string>

#include "TaskManager.h"

/**
 * @brief 用户类，包含用户名和密码散列
 */
class User
{
public:
    /**
     * @brief 构造函数，初始化用户名和密码散列
     * @param username 用户名
     * @param passwordHash 密码散列
     */
    User(const std::string &username, const std::string &passwordHash);

    /**
     * @brief 获取用户名
     * @return 返回用户名
     */
    std::string getUsername() const;

    /**
     * @brief 获取密码散列
     * @return 返回密码散列
     */
    std::string getPasswordHash() const;

    /**
     * @brief 获取该用户的任务管理器
     * @return 返回该用户的任务管理器
     */
    TaskManager getTaskManager() const;

    /**
     * @brief 散列密码
     * @param password 明文密码
     * @return 返回散列后的密码
     */
    static std::string hashPassword(const std::string &password);

    /**
     * @brief 注册函数
     * @param 
     * @return 是否成功注册 （检查用户名是否重复）
     */
    bool registeR();

    /**
     * @brief 登录函数
     * @param
     * @return 是否成功登录 （检查用户名是否存在（位于users.txt中），检查密码是否正确）
     */
    static bool login(const std::string &username, const std::string &passwordHash);

    

private:
    std::string username;     ///< 用户名
    std::string passwordHash; ///< 密码散列
    TaskManager manager;      // 该用户的任务管理器
};

#endif // USER_H
