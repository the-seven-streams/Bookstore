var http = require('http');
var fs = require('fs');
var socketio = require('socket.io');
var server = http.createServer(function (request, response) {
    fs.readFile('Bookstore.html', function(error, data) {
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(data);
    });
}).listen(52273, function () {
    console.log('Start!');
});
var io = socketio.listen(server);
io.sockets.on('connection', function (socket) {
    console.log('connected!');
    socket.on('clientData', function(data) {
        console.log('数据：', data);
        socket.emit('serverData', data);
    });
});