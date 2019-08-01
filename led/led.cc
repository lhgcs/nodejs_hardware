/*
 * @Description: led
 * @Author: your name
 * @Date: 2019-07-15 12:02:36
 * @LastEditTime: 2019-08-01 10:44:31
 * @LastEditors: Please set LastEditors
 */

// #include </usr/include/nodejs/deps/v8/include/v8.h>
// #include </usr/include/nodejs/src/node.h>

#include <node.h>
#include <v8.h>
using namespace v8;

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>

namespace led {

    /**
     * @description: 控制led亮灭
     * @param {type} LED名称
     * @param {type} 电平
     * @return: 
     */   
    // 输入参数使用 const FunctionCallbackInfo<Value>& args 结构传入
    void led_on_or_off(const FunctionCallbackInfo<Value>& args) {
        // 使用 HandleScope 来管理生命周期
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);

        // 判断参数类型
        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        if (!args[0]->IsString() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }


        Local<String> value2 = Local<String>::Cast(args[0]);
        String::Utf8Value utfValue(value2);
        std::string device = std::string(*utfValue);
        std::cout << device << std::endl;

        // int value = args[1]->IntegerValue();
        // std::cout << "first argument = " << value << std::endl;

        Local<Number> value1 = Local<Number>::Cast(args[1]);
        int value = value1->IntegerValue();
        std::cout << value << std::endl;

        // 设备
	    char deviceName[64];
        char level[20];
        memset(deviceName, 0, sizeof(deviceName));
        memset(level, 0, sizeof(level));

        if(0 == device.compare("wifi")) {
            strcpy(deviceName, "/sys/class/leds/led-wifi/trigger");
        }else if(0 == device.compare("usr1")) {
            strcpy(deviceName, "/sys/class/leds/led-usr1/trigger");
        }else if(0 == device.compare("usr2")) {
            strcpy(deviceName, "/sys/class/leds/led-usr2/trigger");
        }else {
            return;
        }

        switch(value) {
            case 0: strcpy(level, "none");       break;//灭
            case 1: strcpy(level, "default-on"); break;//亮
            default: strcpy(level, "heartbeat"); break;//闪烁
        }
        
        int ret = 0;
        int fd = open(deviceName, O_WRONLY);
        if(fd > 0) {
            printf("open %s\n", deviceName);
            int len =write(fd, level, strlen(level));
            printf("len:%d\n", len);
            close(fd);
        } else {
            printf("can not open %s\n", deviceName);
            ret = -1;
        }

        // 声明
        Local<Number> num = Number::New(isolate, ret);
        // 设置返回值
        args.GetReturnValue().Set(num);
    }


    /**
     * @description: 初始化函数(名字随便起)
     * @param {type} 
     * @return: 
     */
    //void init(Handle<Object> exports) {
    void Initialize(Local<Object> exports) {
        //导出方法 NODE_SET_METHOD(exports, Method_Name, Method)
        NODE_SET_METHOD(exports, "led_on_or_off", led_on_or_off)
    }


    /**
     * @description: 导出初始化函数
     * @param {type} 
     * @return: 
     */
    //NODE_GYP_MODULE_NAME是在binding.gyp中设定的模块名称，NODE_MODULE不是函数，所有不需要;结尾
    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo