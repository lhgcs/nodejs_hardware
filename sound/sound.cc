/*
 * @Description: 播放音频
 * @Author: your name
 * @Date: 2019-07-15 12:02:36
 * @LastEditTime: 2019-07-24 15:22:31
 * @LastEditors: Please set LastEditors
 */



#include <node.h>
#include <v8.h>

using namespace v8;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace sound {

    /**
     * @description: 执行shell命令并返回结果
     * @param {type} 
     * @return: 
     */
    int system_shell(const char *cmdString) {
        int ret = -1;
        if(NULL == cmdString) {
            return -1;
        }
        ret = system(cmdString);

        return ret == 0 ? 0 : -1;
    }


    /**
     * @description: 播放音频
     * @param {type} 
     * @return: 
     */
    void play(const FunctionCallbackInfo<Value>& args) {
        //一个独立的V8执行环境
        Isolate* isolate = args.GetIsolate();
        HandleScope scope(isolate);

        // 判断参数类型
        if (args.Length() < 1 || !args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
            return ;
        }

        String::Utf8Value utfValue(Local<String>::Cast(args[0]));
        std::string fileName = std::string(*utfValue);

        system_shell(fileName.c_str());
    }


    /**
     * @description: 初始化函数(名字随便起)
     * @param {type} 
     * @return: 
     */
    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "play", play);
    }

    /**
     * @description: 导出初始化函数
     * @param {type} 
     * @return: 
     */
    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo