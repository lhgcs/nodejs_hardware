/*
 * @Description: 播放音频
 * @Author: your name
 * @Date: 2019-07-15 12:02:36
 * @LastEditTime: 2019-08-01 18:07:29
 * @LastEditors: Please set LastEditors
 */

#include <node.h>
#include <v8.h>

using namespace v8;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <unistd.h>
#include <fcntl.h>

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
     * @description: 读文件
     * @param {type} 
     * @return: 
     */
    int read_file(const char *fileName, char *data, int dataSize) {
        int ret = -1;
        int fd = open(fileName, O_RDONLY);
        if(fd > 0) {
            ret =read(fd, data, dataSize);
            close(fd);
        } else {
            printf("can not open %s\n", fileName);
        }
        return ret;
    }


     /**
     * @description: 去除左边空格
     * @param {type} 
     * @return: 
     */
    char *strltrim(char *s) {
        char *p = s;

        if (NULL == *p) {
            return NULL;
        }

        while(*p != '\0') {
            if ((*p == ' ') || (*p == '\t') || (*p == '\r') || (*p == '\n')) {
                p++;
            } else {
                break;
            }
        }
        return p;
    }

	
    /**
     * @description: 去除右边空格
     * @param {type} 
     * @return: 
     */
    char *strrtrim(char *s) {
        char *p = s;

        if (NULL == *p) {
            return NULL;
        }
        //找到最右边的字符
        while(*p != '\0') {
            p++;
        }
        p--;

        while(p >= s) {
            if ((*p == ' ') || (*p == '\t') || (*p == '\r') || (*p == '\n')) {
                *p = '\0';
                if(p > s) {
                    p--;
                }
            } else {
                break;
            }
        }
        return s;
    }
	

    /**
     * @description: 去除两边空格
     * @param {type} 
     * @return: 
     */
    char *strtrim(char *s) {
        char *p = strltrim(s);
        char *q = strrtrim(p);
        return q;
    }


    /**
     * @description: 获取cpuid
     * @param {type} 
     * @return: 
     */
    void get_cpu_id(const FunctionCallbackInfo<Value>& args) {
        //一个独立的V8执行环境
        Isolate* isolate = args.GetIsolate();
        HandleScope scope(isolate);

        char data[256];
        memset(data, 0, sizeof(data));

        if(read_file("/sys/firmware/devicetree/base/serial-number", data, sizeof(data)) > 0) {  
            data = strtrim(data);
            if(strlen(data) <= 0) {
                memcpy(data, "000000");
            }
        } else {
            memcpy(data, "000000");
        }

        std::string str = data;

        // 设置返回值
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());
    }


    /**
     * @description: 获取cpu温度
     * @param {type} 
     * @return: 
     */
    void get_cpu_temp(const FunctionCallbackInfo<Value>& args) {
        //一个独立的V8执行环境
        Isolate* isolate = args.GetIsolate();
        HandleScope scope(isolate);

        int temp = 0;
        char data[256];
        memset(data, 0, sizeof(data));

        if(read_file("/sys/devices/virtual/thermal/thermal_zone0/temp", data, sizeof(data)) > 0
        || read_file("/sys/class/thermal/thermal_zone0/temp", data, sizeof(data)) <= 0) {  
            data = strtrim(data);
            int index = strlen(data) - 3;
            for(int i=0; i < index; i++) {
                if(data[i] >= '0' && data[i] <= '9') {
                    temp = temp * 10 + (data[i] - '0');
                } elae {
                    temp = 0;
                    break;
                }
            } 
        }

        // 设置返回值
        args.GetReturnValue().Set(Number::New(isolate, value));
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