var test = require('./build/Release/cpu');
// 获取CPU ID
console.log(test.get_cpu_id());
// 获取CPU温度
console.log(test.get_cpu_temp());