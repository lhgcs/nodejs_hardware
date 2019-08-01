
//使用require加载插件
var led = require('./build/Release/led');
// LED灭
console.log(led.led_on_or_off("usr2", 0));
// // LED亮
// console.log(led.led_on_or_off("usr2", 1));
// // LED闪烁
// console.log(led.led_on_or_off("usr2", 2));