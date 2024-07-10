//Web服务器设置

const express = require('express');//创建和管理服务器及其路由
const session = require('express-session')//管理会话
const path = require('path');
const app = express();
const port = 4444;

//设置跨域访问
app.use(express.json());//解析JSON的请求
app.use(express.urlencoded({ extended: false }));//解析URL编码的请求
app.use(express.static(path.join(__dirname, 'public')));//托管静态文件

//设置session
app.use(
  session({
    secret: 'secretKey', //签名会话ID的cookie密钥
    resave: false,
    saveUninitialized: false,
  })
);

//导入路由
const router1 = require('./router');
app.use('/', router1);


//启动服务器
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});