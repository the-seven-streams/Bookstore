var http = require("http");
var fs = require("fs");
var {spawn} = require('child_process');
var socketio = require("socket.io");
var run = spawn('./code');//初始化
var server = http.createServer(function(request, response) {
  fs.readFile("main.html", function(error, data) {
    response.writeHead(200, {"Content-Type": "text/html"});
    response.end(data);
  });
}).listen(52273, function() {
  console.log("START");  
  run = spawn('./code');//初始化
});
var io = socketio.listen(server);
io.sockets.on("connection", function(socket) {
  console.log("CONNECTED!")
  run.stdout.on('Data', function(Data) {
    socket.emit('serverdata', {text: Data.toString()});//向客户端发送数据
  })
  socket.on('clientdata', function(data) {
    console.log('RECEIVED DATA');
    run.stdin.write(data);//接收客户端数据
  })
});