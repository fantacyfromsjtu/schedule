#ifndef USER_H
#define USER_H

#include <string>

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
     * @brief 散列密码
     * @param password 明文密码
     * @return 返回散列后的密码
     */
    static std::string hashPassword(const std::string &password);

private:
    std::string username;     ///< 用户名
    std::string passwordHash; ///< 密码散列
};

#endif // USER_H
