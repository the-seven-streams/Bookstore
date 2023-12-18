var http = require("http");
var fs = require("fs");
var {spawn} = require('child_process');
var socketio = require("socket.io");
var run;
var server = http.createServer(function(request, response) {
  fs.readFile("main.html", function(error, data) {
    response.writeHead(200, {"Content-Type": "text/html"});
    response.end(data);
  });
}).listen(52273, function() {
  console.log("START");  
  run = spawn('./code.exe');//初始化
});
var io = socketio.listen(server);
io.sockets.on("connection", function(socket) {
  socket.on('clientdata', function(clientdata) {
    var txt;
    run.stdin.write(clientdata + '\n');//接收客户端数据
    run.stdout.on('data', function(data) {
      txt = data.toString();
      console.log(txt);
      socket.emit('serverdata', txt);//发送数据给客户端
      run.stdout.removeAllListeners('data');
    })
  })
});
io.sockets.on('serverdata', function(data) {
  console.log(data);
});