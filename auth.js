//用户认证模块

function checkUser(req, res, next) {
  if(req.session && req.session.user) next()
  else {
    res.status(401)
    res.send("401 Unauthorized")
  }
}

const auth = {
  checkUser,
};

module.exports = auth;
