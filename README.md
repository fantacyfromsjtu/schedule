# 项目运行说明

## 命令行版本

### 1. 安装依赖（Ubuntu环境）

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev
```

### 2. 项目运行

```bash
cd CLI
mkdir build  //如果build不存在
cd build
cmake ..
make
./ScheduleManager_CLI -h   //查看帮助
./ScheduleManager_CLI run  //启动程序
```



## Web版本

### 1. 安装依赖

```bash
cd web
npm install express crypto
```

### 2. 运行本地服务

在 `web` 目录下运行以下命令启动本地服务：

```bash
node index.js
```

### 6. 访问 Web 页面

打开浏览器，访问以下 URL 进入页面：

http://localhost:4444/
