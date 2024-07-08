const express = require('express');
const controller = require('./controller');
const router = express.Router();

// 定义路由和对应的控制器方法
router.get('/login', controller.login);
router.post('/signup', controller.signup);
// 更多路由...

module.exports = router;