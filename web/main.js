const https = require("https");
const fs = require("fs");
const spawn = require('child_process');
const socketio = require("socket.io");
var server = https.createServer(function(request, response) {
  fs.readFile("main.html", function(error, data) {
    response.writeHead(200, {"Content-Type": "text/html"});
    response.end(data);
  });
}).listen(52273, function() {
  console.log("START");  
});
var io = socketio.listen(server);
io.sockets.on("connection", function(socket) {
  run = spawn('./code');//初始化
  run.stdout.on('Data', function(Data) {
    socket.emit('serverdata', {text: Data.toString()});//向客户端发送数据
  })
  socket.on('clientdata', function(data) {
    spawn.stdin.write(data.text);//向子进程发送数据
  })
});