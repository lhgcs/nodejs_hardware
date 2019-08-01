
//使用require加载插件
var led = require('./build/Release/led');
console.log(led.led_on_or_off("usr2", 2));

//bindings包来加载已编译的模块,实际上使用的try-catch模式
//ar led = require('led')('led.node');
// module.exports.obj = obj;
