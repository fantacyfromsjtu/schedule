根据上述设计思路，这里是一个详细的文件目录结构，可以用于你的日程管理软件项目。该目录结构分为源代码、头文件、数据文件和其他辅助文件。

### 文件目录结构

```
ScheduleManager/
├── src/
│   ├── main.cpp                 # 主程序入口
│   ├── User.cpp                 # User类实现
│   ├── Task.cpp                 # Task类实现
│   ├── TaskManager.cpp          # TaskManager类实现
│   ├── Reminder.cpp             # Reminder类实现
│   ├── Utils.cpp                # 辅助函数实现
│   ├── TimeUtils.cpp            # 时间处理工具类实现
|   |—— Interact.cpp             # 用户交互类的实现
├── include/
│   ├── User.h                   # User类定义
│   ├── Task.h                   # Task类定义
│   ├── TaskManager.h            # TaskManager类定义
│   ├── Reminder.h               # Reminder类定义
│   ├── Utils.h                  # 辅助函数定义
│   ├── TimeUtils.h              # 时间处理工具类定义
|   |—— Interact.h               # 用户交互类定义
├── data/
│   ├── users.txt                # 用户信息文件
│   ├── tasks_user1.txt          # 用户1的任务文件
│   └── tasks_user2.txt          # 用户2的任务文件
├── CMakeLists.txt               # CMake构建文件
└── README.md                    # 项目说明文件

```

### 文件详细描述

#### `src/`
- `main.cpp`：程序的入口文件，负责初始化和启动程序。
- `User.cpp`：`User` 类的实现文件，包含用户注册、登录和密码加密等功能。
- `Task.cpp`：`Task` 类的实现文件，包含任务属性的设置和获取方法。
- `TaskManager.cpp`：`TaskManager` 类的实现文件，负责管理任务的增删改查和任务的持久化。
- `Reminder.cpp`：`Reminder` 类的实现文件，负责多线程定期检查任务并提醒用户。
- `Utils.cpp`：辅助函数的实现文件，如文件读写、字符串处理等。

#### `include/`
- `User.h`：`User` 类的头文件，定义了用户类的属性和方法。
- `Task.h`：`Task` 类的头文件，定义了任务类的属性和方法。
- `TaskManager.h`：`TaskManager` 类的头文件，定义了任务管理类的属性和方法。
- `Reminder.h`：`Reminder` 类的头文件，定义了任务提醒类的属性和方法。
- `Utils.h`：辅助函数的头文件，声明了各种实用工具函数。

#### `data/`
- `users.txt`：保存用户信息的文件，包含用户名和加密后的密码。
- `tasks_user1.txt`：保存用户1的任务信息。
- `tasks_user2.txt`：保存用户2的任务信息。

#### `CMakeLists.txt`
- 用于项目的构建配置文件，包含编译选项和依赖关系。

#### `README.md`
- 项目的说明文件，提供项目简介、使用说明、开发者指南等。

### 项目构建和运行

在项目根目录下，可以使用CMake构建项目：

```sh
mkdir build
cd build
cmake ..
make
```

生成的可执行文件将在 `build` 目录中。可以通过运行生成的可执行文件来启动程序：

```sh
./ScheduleManager run
```

