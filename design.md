# ScheduleManager项目设计文档

## 1. 小组成员与分工

| 姓名   | 邮箱                      | 分工                 |
| ------ | ------------------------- | -------------------- |
| 王桢锐 | blizzard-wang@sjtu.edu.cn | 负责命令行版本的实现 |
| 何昊聪 | haocong-he@sjtu.edu.cn    | 负责Web版本的实现    |



## 2.  命令行版本设计

### （1）模块与类的设计

命令行版本的总体设计如下：

```bash
schedule/
├── CLI/
│   ├── build/                      # 编译生成的目录，包含生成的可执行文件
│   ├── include/                    # 头文件目录
│   │   ├── Interact.h              # 与用户交互相关的函数声明
│   │   ├── Reminder.h              # 提醒功能相关的类声明
│   │   ├── Task.h                  # 任务类的声明
│   │   ├── TaskManager.h           # 任务管理类的声明
│   │   ├── TimeUtils.h             # 时间处理工具函数的声明
│   │   ├── User.h                  # 用户类的声明
│   │   ├── Utils.h                 # 工具函数的声明
│   ├── src/                        # 源文件目录
│   │   ├── main.cpp                # 项目的主程序入口
│   │   ├── Interact.cpp            # 与用户交互相关的函数实现
│   │   ├── Reminder.cpp            # 提醒功能相关的类实现
│   │   ├── Task.cpp                # 任务类的实现
│   │   ├── TaskManager.cpp         # 任务管理类的实现
│   │   ├── TimeUtils.cpp           # 时间处理工具函数的实现
│   │   ├── User.cpp                # 用户类的实现
│   │   ├── Utils.cpp               # 工具函数的实现
│   ├── test.sh                     # 自动化测试脚本，用于测试命令行版本的功能
│   ├── CMakeLists.txt              # CMake 配置文件，用于生成项目的构建系统
├── web/                            # Web 版本的代码和相关文件
|...
```



## 3. Web版本设计

