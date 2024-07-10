//数据库交互模块

const sqlite3 = require("sqlite3").verbose(); // 导入 sqlite3 库用于操作 SQLite 数据库，verbose() 开启详细日志模式。
const CryptoJS = require('crypto-js'); // 导入 CryptoJS 库用于密码加密。
const sqlite = require("sqlite"); // 导入 sqlite 库提供了更高级的接口来操作 SQLite 数据库。

const dbPath = './database/data.db';
const sqlPath = './database/data.sqlite';


async function openDB() {
  return sqlite.open({
    filename: dbPath, // 指定数据库文件路径
    driver: sqlite3.Database //指定使用 sqlite3 作为驱动
  })
}

// 初始化数据库，创建 Tasks 和 Users 表
async function initialize() {
  const db = await openDB();

  await db.run(`
  CREATE TABLE IF NOT EXISTS Tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT, -- 给每个任务分配唯一的id
    name TEXT NOT NULL,
    startTime TEXT UNIQUE NOT NULL, -- 每个任务的开始时间不能相同
    priority TEXT,
    category TEXT,
    reminderTime TEXT,
    user INTEGER, 
    done BOOL
  )
`);

  await db.run(`
  CREATE TABLE IF NOT EXISTS Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
  )
`);

  db.close();
}

async function addUser(username, password) {
  const db = await openDB();

  const sql = 'INSERT INTO Users (username, password) VALUES (?, ?)';
  var encryptedPassword = CryptoJS.SHA256(password).toString();
  const values = [username, encryptedPassword];
  console.log(encryptedPassword);

  try {
    const result = await db.run(sql, values);
    console.log('用户注册成功(*^▽^*)');
    console.log('用户ID:', result.lastID);
  } catch (err) {
    console.error('用户添加失败:', err);
    throw (err);
  } finally {
    db.close();
  }
}


async function addTask(name, startTime, priority, category, reminderTime, userId) {
  const db = await openDB();
  let rst = false;  //用于表示任务添加操作的成功与否

  // done列被明确设置为false，表示这是一个新任务，尚未完成
  const sql = `
      INSERT INTO Tasks (name, startTime, priority, category, reminderTime, user, done)
      VALUES (?, ?, ?, ?, ?, ?, false)
    `;
  const values = [name, startTime, priority, category, reminderTime, userId];

  try {
    const row = await db.run(sql, values);
    console.log('任务添加成功(*^▽^*)');
    console.log('任务ID:', row.lastID);
    rst = true;
  } catch (err) {
    console.error('添加任务失败:', err)
  } finally {
    db.close();
  }
  return rst;
}

//从数据库中按日期查询任务
async function showTaskByDate(date) {
  const db = await openDB();
  let rst = []; // 用于存储查询结果

  const sql = `
    SELECT * FROM Tasks WHERE startTime like '${date}%'
  `;

  try {
    const rows = await db.all(sql, [`${date}%`]); //参数化查询避免SQL注入
    console.log(rows);

    rst = rows.map((row) => {
      return {
        taskId: row.id,
        name: row.name,
        startTime: row.startTime,
        priority: row.priority,
        category: row.category,
        reminderTime: row.reminderTime,
        userId: row.user,
        done: row.done
      };
    });

    console.log('按照日期显示成功');
  } catch (err) {
    console.log(err);
    throw(err);
  } finally {
    db.close ();
    return rst;
  }
}

async function deleteTask(taskId) {
  const db = await openDB();

  const sql = 'DELETE FROM Tasks WHERE id = ?';
  const values = [taskId];
  let rst = false;  //用于表示任务删除操作的成功与否

  try {
    const result = await db.run(sql, values);
    console.log(result);

    if (result.changes>0){
      console.log('成功删除任务', taskId, '!');
      rst = true;
    }
    else{
      console.log('不存在任务', taskId, '.');
    }
  } catch (err) {
    console.error('删除出现错误:', err);
  } finally {
    db.close();
  }
  return rst;
}


async function loginUser(username, password) {
  const db = await openDB();
  let rst = 0; //用于表示用户登录操作的成功与否
  const sql = 'SELECT id FROM Users WHERE username = ? AND password = ?';
  const encryptedPassword = CryptoJS.SHA256(password).toString();
  const values = [username, encryptedPassword];

  try {
    const row = await db.get(sql, values);
    if (row) {
      console.log('登陆成功~');
      console.log('用户ID:', row.id);
      rst = row.id; 
    } else {
      console.log('登录失败：用户名或密码错误 o(╥﹏╥)o');
      rst = 0; 
    }
  } catch (err) {
    console.log(err);
    rst = 0;
  } finally {
    db.close();
  }
  return rst;
}

async function changePassword(userId, newPassword) {
  const db = await openDB();

  const sql = 'UPDATE Users SET id = ? WHERE password = ?';
  const encryptedNewPassword = CryptoJS.SHA256(newPassword).toString();
  const values = [encryptedNewPassword, userId];
  let rst = false;

  try {
    const result = await db.run(sql, values); 
    if (result.stmt.changes > 0) { 
      console.log('密码修改成功~');
      rst = true;
    } else {
      console.log('未找到该用户');
      rst = false;
    }
  } catch (err) {
    console.log('密码修改失败: ', err);
    throw (err);
  } finally {
    db.close();
  }
  return rst; 
}

async function checkTaskUser(taskId, userId) {  // Retrieve the username and password from the request body or headers

  const db = await openDB();
  const sql = `SELECT * FROM Tasks WHERE id = ? AND user = ?`;
  let rst = false;

  try {
    const row = await db.get(sql, [taskId, userId]);
    rst = (row != null);
  } catch (err) {
    console.log(err);
  } finally {
    db.close();
  }
  return rst;
}


// 查询用户所有任务
async function queryTasks(user) {
  const db = await openDB();

  const sql = 'SELECT * FROM Tasks WHERE user = ?';
  const values = [user];

  try {
    const rows = await db.all(sql, values);
    const tasks = rows.map((row) => {
      return {
        taskId: row.id,
        name: row.name,
        startTime: row.startTime,
        priority: row.priority,
        category: row.category,
        reminderTime: row.reminderTime,
        userId: row.user,
        done: row.done
      };
    });
    return JSON.stringify(tasks);
  } catch (err) {
    console.error('Error querying tasks:', err);
    return null;
  } finally {
    db.close();
  }
}

const services = {
  initialize,
  addUser,
  addTask,
  showTaskByDate,
  deleteTask,
  loginUser,
  changePassword,
  queryTasks,
  checkTaskUser
};

// Export the services object
initialize()

module.exports = services;