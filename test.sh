#!/bin/bash

# 提示确认
echo "如果运行将会清除所有用户信息，确认运行？(y/n)"
read confirmation
if [ "$confirmation" != "y" ]; then
    echo "操作已取消。"
    exit 1
fi

# 清理环境
rm -rf build
mkdir build
cd build
cmake ..
make

# 清空用户和任务数据
> ../data/users.txt
rm -f ../data/tasks/*

# 生成当前时间加1, 2, 3, 4, 5分钟的时间字符串
start_time1=$(date -d "+1 minute" "+%Y-%m-%d %H:%M:%S")
start_time2=$(date -d "+2 minutes" "+%Y-%m-%d %H:%M:%S")
start_time3=$(date -d "+3 minutes" "+%Y-%m-%d %H:%M:%S")
start_time4=$(date -d "+4 minutes" "+%Y-%m-%d %H:%M:%S")
start_time5=$(date -d "+5 minutes" "+%Y-%m-%d %H:%M:%S")

remind_time1=$(date -d "+30 seconds" "+%Y-%m-%d %H:%M:%S")
remind_time2=$(date -d "+1 minute 30 seconds" "+%Y-%m-%d %H:%M:%S")
remind_time3=$(date -d "+2 minutes 30 seconds" "+%Y-%m-%d %H:%M:%S")
remind_time4=$(date -d "+3 minutes 30 seconds" "+%Y-%m-%d %H:%M:%S")
remind_time5=$(date -d "+4 minutes 30 seconds" "+%Y-%m-%d %H:%M:%S")

# 创建Expect脚本
expect << EOF
#!/usr/bin/expect

set timeout -1

# 注册用户
spawn ./ScheduleManager run
expect "注册（输入r） or 登录（输入l） or 退出（输入q）"
send "r\n"
expect "用户名:"
send "testuser\n"
expect "密码:"
send "testpassword\n"
expect "注册成功！"
send "q\n"

# 登录用户
spawn ./ScheduleManager run
expect "注册（输入r） or 登录（输入l） or 退出（输入q）"
send "l\n"
expect "用户名:"
send "testuser\n"
expect "密码:"
send "testpassword\n"
expect "登录成功！"

# 添加任务1
expect "请输入命令："
send "addtask\n"
expect "任务名："
send "Test Task 1\n"
expect "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）："
send "$start_time1\n"
expect "优先级（默认为medium）："
send "high\n"
expect "任务种类（默认为other）："
send "work\n"
expect "任务提醒时间（默认为任务开始时间）："
send "$remind_time1\n"

# 添加任务2
expect "请输入命令："
send "addtask\n"
expect "任务名："
send "Test Task 2\n"
expect "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）："
send "$start_time2\n"
expect "优先级（默认为medium）："
send "medium\n"
expect "任务种类（默认为other）："
send "study\n"
expect "任务提醒时间（默认为任务开始时间）："
send "$remind_time2\n"

# 添加任务3
expect "请输入命令："
send "addtask\n"
expect "任务名："
send "Test Task 3\n"
expect "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）："
send "$start_time3\n"
expect "优先级（默认为medium）："
send "low\n"
expect "任务种类（默认为other）："
send "life\n"
expect "任务提醒时间（默认为任务开始时间）："
send "$remind_time3\n"

# 添加任务4
expect "请输入命令："
send "addtask\n"
expect "任务名："
send "Test Task 4\n"
expect "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）："
send "$start_time4\n"
expect "优先级（默认为medium）："
send "medium\n"
expect "任务种类（默认为other）："
send "work\n"
expect "任务提醒时间（默认为任务开始时间）："
send "$remind_time4\n"

# 添加任务5
expect "请输入命令："
send "addtask\n"
expect "任务名："
send "Test Task 5\n"
expect "任务开始时间（格式为YYYY-MM-DD HH:MM:SS）："
send "$start_time5\n"
expect "优先级（默认为medium）："
send "high\n"
expect "任务种类（默认为other）："
send "study\n"
expect "任务提醒时间（默认为任务开始时间）："
send "$remind_time5\n"

# 显示任务
expect "请输入命令："
send "showtask\n"
expect "查看任务的月份(格式：两位数字)：(可以跳过，默认为当月)"
send "07\n"
expect "查看任务的日期(格式：两位数字)：(可以跳过，默认显示每一天)"
send "\n"

# 删除任务3
expect "请输入命令："
send "deltask\n"
expect "输入要删除的任务id："
send "3\n"
expect "确认删除任务：3 ?(y/n)"
send "y\n"

# 显示任务
expect "请输入命令："
send "showtask\n"
expect "查看任务的月份(格式：两位数字)：(可以跳过，默认为当月)"
send "\n"
expect "查看任务的日期(格式：两位数字)：(可以跳过，默认显示每一天)"
send "\n"

# 退出系统
expect "请输入命令："
send "q\n"

expect eof
EOF
