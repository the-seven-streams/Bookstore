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
}).listen(52273,'0.0.0.0', function() {
  console.log("START");  
  run = spawn('./code');//初始化
});
var io = socketio.listen(server);
io.sockets.on("connection", function(socket) {
  socket.on('clientdata', function(clientdata) {
    run.stdin.write(clientdata + '\n');//接收客户端数据
    run.stdout.on('data', function(data) {
      run.stdout.removeAllListeners('data');
      var txt;
      txt = data.toString();
      io.emit('serverData', txt);//发送数据给客户端
    })
  })
});