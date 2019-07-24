//hello接受两个参数，一个字符串，一个回调函数：
var test = require('./build/Release/hello');
test.hello('test', function(data) {
    console.log(data);
});
