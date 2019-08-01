var test = require('./build/Release/wifi');
// 当前是否连接网络
//console.log(test.isConnect());
// 清空连接记录
//console.log(test.clearAllWifi());
// 连接
console.log(test.connect2wifi("YrxGz", "12345678"));
