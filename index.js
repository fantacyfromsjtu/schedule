const express = require('express');
const session = require('express-session');
const app = express();
const router = require('./router');

app.use(express.json()); // 解析JSON请求体
app.use(express.static('public')); // 设置静态资源目录
app.use(session({
  secret: 'your session secret', // 用于签名session ID的字符串
  resave: false,
  saveUninitialized: true,
}));

app.use(router); // 使用路由

const PORT = 3000;
app.listen(PORT, () => console.log(`Server is running on http://localhost:${PORT}`));