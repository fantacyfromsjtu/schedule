cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(ScheduleManager VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置源文件列表
set(SRC_FILES
    src/main.cpp
    src/User.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/Reminder.cpp
    src/Utils.cpp
    src/TimeUtils.cpp
    src/Interact.cpp
)

# 生成可执行文件
add_executable(ScheduleManager ${SRC_FILES})

# 链接线程库
find_package(Threads REQUIRED)
target_link_libraries(ScheduleManager Threads::Threads)

# 链接 OpenSSL 库
find_package(OpenSSL REQUIRED)
target_link_libraries(ScheduleManager OpenSSL::SSL OpenSSL::Crypto)
