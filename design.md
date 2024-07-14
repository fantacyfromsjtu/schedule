# ScheduleManager项目设计文档

## 1. 小组成员与分工

| 姓名   | 邮箱                      | 分工                 |
| ------ | ------------------------- | -------------------- |
| 王桢锐 | blizzard-wang@sjtu.edu.cn | 负责命令行版本的实现 |
| 何昊聪 | haocong-he@sjtu.edu.cn    | 负责Web版本的实现    |



## 2.  命令行版本设计
### 2.1 模块与类的设计

命令行版本的总体设计如下：

本项目严格遵从C++面向对象编程的思想，采用模块化编程。对于所有类均给出头文件和源文件。

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

本项目主要包含五大模块：**交互模块，用户管理模块，任务管理模块，工具函数模块，以及测试模块**。下面依次进行说明。



**交互模块**

主要由main.cpp 以及Interact类组成，负责处理用户输入。main主要处理用户的第一层输入，比如登录注册等等。而具体的第二层输入（例如增加删除任务等等），则交由Interact模块完成。



**用户管理模块**

主要由User类完成，负责用户的注册，登录等功能。支持多用户，保证每个用户的任务相互独立。另外，我们还额外实现了修改密码功能。



**任务管理模块**

本模块是项目的核心模块，主要由Task类，TaskManager类，Reminder类组成。

Task类包含单个任务的各种属性及其接口。

TaskManager类是任务的“统领”，每一个用户都绑定一个TaskManager，其核心是维护一个元素为Task的vector，包含对该用户任务的增加，删除，查询等操作。

Reminder类是实现任务提醒的类，提醒线程实现每10秒检查一次有没有任务需要提醒。



**工具函数模块**

本模块主要由Utils类TimeUtils类组成

TimeUtils类实现了与时间相关的辅助函数，例如获取当前时间，以及时间的字符串-std::chrono::system_clock::time_point（C++11标准库的系统时间）的相互转换

Util类实现了其他一些辅助函数，例如SHA256哈希函数，颜色设置等函数



**测试模块**

test.sh，完成自动化测试

### 2.2 流程图

![image-20240714231844899](E:\大学\大学学习all in one\大二暑期课程\计算机编程实践\proj\assets\image-20240714231844899.png)

### 2.3  关键技术问题实现

#### 2.3.1 多线程

在项目中，多线程机制主要体现在 `Reminder` 类的实现上。`Reminder` 类通过一个独立的线程不断检查是否有任务需要提醒。

**`Reminder::start` 函数**:

```cpp
void Reminder::start()
{
    running = true;
    reminderThread = std::thread([this]()
                                 {
        while (running) {
            checkReminders();
            std::this_thread::sleep_for(std::chrono::seconds(10)); // 每10s检查一次
        } });
}

```

- `std::thread`：用于创建一个新的线程，在本例中，启动一个线程来定期检查任务提醒。
- `std::this_thread::sleep_for`：使线程睡眠指定时间段，这里是10秒，表示每10秒检查一次任务提醒。

为了防止多个线程同时对Task列表或者任务文件进行写操作，或者当一个线程进行写操作时，另一个文件进行读操作，需要引入互斥锁，以实现多个线程对临界资源的互斥访问。

```cpp
namespace Utils
{
    std::mutex mtx;
}
```

- `std::mutex mtx`：在 `Utils` 命名空间中定义一个互斥锁实例 `mtx`。

使用实例（删除任务）

```cpp
void ask_del(TaskManager &usermanager)
{
	...  
    if (yorn == 'y' || yorn == 'Y') //确认删除
    {
        std::lock_guard<std::mutex> lock(Utils::mtx); // 加锁
        bool isdel = usermanager.deleteTask(id);
        ...
    }
}

```

- `std::lock_guard<std::mutex>`：RAII 方式管理互斥锁，**在构造时自动获取锁，在析构时自动释放锁**，避免手动调用 `lock` 和 `unlock` 带来的错误。

当然，在添加任务，显示任务，提醒线程遍历任务等涉及到读写文件和修改Task列表的操作时，也要进行加锁操作。另外，由于提醒线程每10s才检查一次，检查完立刻释放锁，所以不会引起死锁的问题。

#### 2.3.2 时间的获取与处理

本项目中时间的获取与处理使用了C++标准库中的`<chrono>`、`<ctime>`、`<iomanip>`、`<sstream>`和`<regex>`，这些库和函数提供了强大的时间管理和字符串处理能力。下面详细解释时间获取与处理的具体实现。

1. 获取当前时间
   - 使用`std::chrono`库获取当前系统时间。
   - 使用`std::time_t`和`std::localtime`函数将系统时间转换为易于操作的时间结构。
2. 格式化时间
   - 使用`std::ostringstream`和`std::put_time`函数将时间结构格式化为字符串。
3. 解析时间
   - 使用`std::istringstream`和`std::get_time`函数将时间字符串解析为时间结构。
4. 验证时间格式
   - 使用正则表达式`<regex>`验证时间字符串格式的合法性。

#### 2.3.3 哈希加密

在本项目中，密码的加密存储是通过使用SHA-256哈希函数实现的。SHA-256是一种加密哈希函数，用于将输入数据转换为固定长度的散列值（哈希值）。该方法确保了密码的安全存储，即使用户信息泄露，攻击者也难以从散列值反推出原始密码。

在项目中，我们使用了OpenSSL库中的EVP（高层加密抽象）接口来实现SHA-256哈希算法。EVP接口提供了一种通用的方式来调用各种加密和哈希算法。

1. **创建并初始化EVP_MD_CTX上下文**
    ```cpp
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_sha256(), nullptr);
    ```
    - `EVP_MD_CTX_new()`：创建一个新的消息摘要上下文。
    - `EVP_DigestInit_ex(context, EVP_sha256(), nullptr)`：初始化上下文以使用SHA-256算法。

2. **更新上下文以包含输入数据**
    ```cpp
    EVP_DigestUpdate(context, str.c_str(), str.size());
    ```
    - `EVP_DigestUpdate(context, str.c_str(), str.size())`：将输入数据添加到上下文中进行处理。

3. **完成哈希计算并获取结果**
    
    ```cpp
    EVP_DigestFinal_ex(context, hash, &lengthOfHash);
    EVP_MD_CTX_free(context);
    ```
    - `EVP_DigestFinal_ex(context, hash, &lengthOfHash)`：完成哈希计算，并将结果存储在`hash`数组中，长度存储在`lengthOfHash`中。
    - `EVP_MD_CTX_free(context)`：释放上下文资源。
    
4. **将结果转换为十六进制字符串表示**
    
    ```cpp
    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    ```
    - 使用`std::stringstream`将每个字节转换为两位的十六进制字符串，并拼接成最终的哈希字符串。





****

## 3. Web版本设计

### 项目结构

```bash
schedule/
├── CLI/
├── web/
│   ├── database/                  # 数据库
│   │   ├── data.db                # sqlite数据库文件
│   │   ├── data.sqlite            # 备份文件
│   ├── public/                    # 静态资源目录，包含前端页面和样式文件
│   │   ├── image/                 # 图片资源
│   │   │   ├── bg.jpg             # 登录页面背景
│   │   │   ├── dashboard.jpg      # 操作页面背景
│   │   │   ├── secret.jpg         # 修改密码页面背景
│   │   ├── Dung_Def_roar_02.ogg   # 提醒音频文件
│   │   ├── login.html             # 用户登录页面
│   │   ├── signup.html            # 用户注册页面
│   │   ├── dashboard.html         # 用户操作界面
│   │   ├── dashboard_2.html
│   │   ├── secret.html            # 修改密码界面
│   │   ├── dashboard_style.css    # 样式表文件
│   │   ├── style.css       
│   │   ├── secret.css
│   ├── auth.js                    # 用户认证模块           
│   ├── controller.js              # 前后端交互控制模块
│   ├── services.js                # 数据库交互模块
│   ├── routes.js                  # 路由配置模块
│   ├── index.js                   # 服务器启动文件
│   ├── package.json               # 项目依赖和配置
```

<<<<<<< HEAD
=======
![image](export.png)

![.\](..\\20200327_1.png "相对路径演示,上一级目录")

>>>>>>> 1f35fb1571a0fb55b5873f6c1c8dbe7fde3cf941
### （1）技术栈
- **前端**：HTML, CSS, JavaScript
- **后端**：Node.js, Express.js
- **数据库**：SQLite
- **安全**：CryptoJS（密码加密）

### （2）模块划分
- **用户认证模块**：处理用户登录、注册、密码修改等认证相关操作。
- **任务管理模块**：提供任务的添加、查询、删除等功能。
- **提醒功能模块**：设置任务提醒，并在指定时间发送提醒。

### （3）关键功能实现
- **用户登录**：通过`/login`路由，使用户能够登录系统。
- **用户注册**：通过`/signup`路由，允许新用户注册账户。
- **密码修改**：通过`/change-password`路由，允许用户修改密码。
- **任务添加**：通过`/add-task`路由，用户可以添加新任务。
- **任务查询**：支持按日期和类别查询任务。
- **任务删除**：通过`/delete-task`路由，用户可以删除指定的任务。

### （4）数据库设计
- **Tasks 表**：存储任务信息，包括任务ID、名称、开始时间、优先级、类别、提醒时间、用户ID和完成状态。
- **Users 表**：存储用户信息，包括用户ID、用户名和加密后的密码。

### （5）安全性考虑
- 使用HTTPS协议保证数据传输安全。
- 密码在存储前使用CryptoJS库进行SHA-256加密。

### （6）部署与运行
- 使用`express`库创建和管理服务器。
- 通过命令行输入`node index.js`运行本地服务。
- 浏览器打开`http://localhost:4444/`访问Web应用。
<<<<<<< HEAD
=======

### 关键技术说明

#### Web服务器构建
使用 `express` 框架来创建和管理服务器及其路由。

#### 用户认证
通过 `session` 中间件管理用户会话，使用 `req.session` 来存储用户登录状态。`checkUser` 函数用于中间件，检查用户是否已登录。

#### 数据库交互
使用 `sqlite3` 和 `sqlite` 库来操作 SQLite 数据库，创建 `Tasks` 和 `Users` 表，并进行数据的增删改查操作。

#### 密码加密
使用 `CryptoJS` 库对用户密码进行 SHA-256 加密，确保存储在数据库中的密码安全性。

#### 路由管理
通过定义不同的路由来处理不同的 HTTP 请求，如登录 (`/login`)、注册 (`/signup`)、任务添加 (`/add-task`)、任务查询 (`/query-tasks`) 等。

#### 静态文件托管
使用 `express.static` 中间件来托管静态文件，如 HTML 页面和 CSS 样式表。

#### 异步操作
大量使用 `async/await` 语法来处理异步数据库操作，提高代码的可读性和维护性。

#### 错误处理
使用 `try/catch` 语句来捕获和处理可能发生的错误，确保程序的健壮性。

#### 安全性
在用户注册和密码修改时，对密码进行加密处理，避免明文密码存储。

#### RESTful API设计
遵循 RESTful 原则设计 API，使用不同的 HTTP 方法（如 GET, POST, DELETE）来实现资源的获取、创建和删除。

#### 前端页面跳转
根据用户的操作结果，使用 `res.redirect` 进行页面跳转，如登录成功后跳转到 `/dashboard`。

#### 服务端渲染
通过 `res.sendFile` 将 HTML 页面作为响应发送给客户端浏览器。

#### 模块化
将不同的功能划分为不同的模块（如 `auth`, `services`, `controller` 等），并使用 `module.exports` 进行导出，提高代码的可维护性和可重用性。

### 项目展示

![image](login.png)

![image](board.png)

![image](secret.png)
>>>>>>> 1f35fb1571a0fb55b5873f6c1c8dbe7fde3cf941
