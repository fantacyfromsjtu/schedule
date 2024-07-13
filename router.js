//路由模块

const express = require('express');
const router = express.Router();
const path = require('path');

const ctrl = require('./controller')
const auth = require('./auth')

//定义根路由
router.get('/', (req, res) => {
  if (req.session && req.session.user) { res.redirect('/dashboard'); }
  else { res.redirect('/login'); }
})

router.get('/login', (req, res) => {
  res.sendFile(path.join(__dirname, 'public','login.html'));
});

router.get('/signup', (req, res) => {
  res.sendFile(path.join(__dirname, 'public','signup.html'));
});

router.get('/change-password', (req, res) => {
  res.sendFile(path.join(__dirname, 'public','secret.html'));
});


// 请求路由
router.post('/login', ctrl.login);

router.post('/signup', ctrl.register);

router.post('/change-password', auth.checkUser, ctrl.changePassword);

router.get('/dashboard', (req, res) => {
  res.sendFile(path.join(__dirname,'public', 'dashboard_2.html'));
});

// 更改密码请求
router.post('/change-password',auth.checkUser, ctrl.changePassword);

// 添加任务请求
router.post('/add-task', auth.checkUser, ctrl.addTask);

// 以时间筛选任务请求
router.get('/tasks', auth.checkUser, ctrl.showTaskByDate);

// 以类别筛选任务请求
router.get('/category', auth.checkUser, ctrl.showTaskByCategory);

// 删除任务请求
router.delete('/delete-task', auth.checkUser, ctrl.deleteTask);

router.get('/query-tasks', ctrl.queryTasks);

// 导出路由
module.exports = router;