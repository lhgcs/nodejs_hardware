/*
 * @Description: wifi
 * @Author: your name
 * @Date: 2019-07-15 11:36:22
 * @LastEditTime: 2019-07-24 15:06:38
 * @LastEditors: Please set LastEditors
 */

#include <node.h>
#include <v8.h>

using namespace v8;

//   // callback, 使用Cast方法来转换
//   Local<Function> callback = Local<Function>::Cast(args[1]);
//   Local<Value> argv[1] = {
//     // 拼接String
//     String::Concat(Local<String>::Cast(args[0]), String::NewFromUtf8(isolate, " world"))
//   };
//   // 调用回调, 参数: 当前上下文，参数个数，参数列表
//   callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);


#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace wifi {

    /**
     * @description: 执行shell命令并返回结果
     * @param {type} 
     * @return: 
     */
    int system_shell(const char *const cmdString) {
        int ret = -1;
        if(NULL == cmdString) {
            return -1;
        }
        ret = system(cmdString);

        return ret == 0 ? 0 : -1;
    }

    /**
     * @description: 执行shell命令并返回结果（创建一个连接到另一个进程（shell的命令行）的管道，然后读其输出或向其输入端发送数据）
     * @param {type} 
     * @return: 
     */
    int popen_shell(const char * const cmdString, char *outString, unsigned int outStringSize) {

        FILE *fp = NULL;
        memset(outString, 0, outStringSize);

        if(NULL == cmdString || NULL == outString) {
            return -1;
        }

        fp = popen(cmdString, "r");
        if (NULL == fp) {
            printf("popen error!\n");
            return -1;
        }

        while (fgets(outString, outStringSize, fp) != NULL) {
            printf("%s", outString);
        }
        pclose(fp);

        return 0;
    }

  
    /**
     * @description: 通过ifconfig检查是否连接到wifi
     * @param {type} 
     * @return: 
     */
    int isConnectByIfconfig() {
        char cmdString[50] = "ifconfig wlan0 | awk 'NR==2 {print $2} ";
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString && NULL != strstr(outString, "192.168")) {
            return 0;
            }
        }

        return -1;
    }


    /**
     * @description: 通过nmcli检查是否连接到wifi
     * @param {type} 
     * @return: 
     */
    int isConnectByNmcli() {
        char cmdString[50] = "nmcli device status | awk 'NR==2 {print $3}";
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString && 0 == strcmp(outString, "connected")) {
            return 0;
            }
        }

        return -1;
    }
  

    /**
     * @description: 获取当前状态
     * @param {type} 
     * @return: 
     */
    int get_status() {
        char cmdString[50] = "nmcli device status | awk 'NR==2 {print $3}";
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString && 0 != strcmp(outString, "")) {
                if(0 == strcmp(outString, "connected")) {
                    return 0;
                } else if(0 == strcmp(outString, "disconnected")) {
                    return 1;
                } else if(0 == strcmp(outString, "connecting")) {
                    return 2;
                } else if(0 == strcmp(outString, "unavailable")) {//不可用
                    return 3;
                } else if(0 == strcmp(outString, "unmanaged")) {//未托管
                    return 4;
                }
            }
        }

        return -1;
    }
  

    /**
     * @description: 是否检测到wifi
     * @param {type} 
     * @return: 
     */
    int is_wifi_exists(const char *wifiName) {
        char cmdString[50] = "nmcli device wifi";
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString && 0 == strcmp(outString, wifiName)) {
                return 0;
            }
        }
        
        return -1;
    }


    /**
     * @description: 当前使用的哪个wifi
     * @param {type} 
     * @return: 
     */
    int is_wifi_use(const char *wifiName) {
        char cmdString[128] = "nmcli device status | awk \'NR==2 {for (i=4;i<=NF;i++)printf(\"%s \", $i);print \"\"}\'";//第4列到最后一列的内容
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString) {

                return 0;
            }
        }
        
        return -1;
    }
  

    /**
     * @description: 打开或关闭wifi
     * @param {type} 
     * @return: 
     */
    int wifi_on_or_off(int onOrOff) {
        char cmdString[50] = "nmcli r wifi ";
        char outString[256];
        if(0 == onOrOff) {
            strcat(cmdString, "off");
        } else {
            strcat(cmdString, "on");
        }

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString) {
                return 0;
            }
        }
        return 0;
    }


    /**
     * @description: 断开wifi
     * @param {type} 
     * @return: 
     */
    int wifi_disconnect() {
        char cmdString[50] = "nmcli device disconnect wlan0";
        char outString[256];

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString) {
                return 0;
            }
        }
        return 0;
    }


  /**
   * @description: 连接wifi
   * @param {type} 
   * @return: 
   */
    int wifi_connect(const char *ssid, const char *password) {
        char cmdString[50];
        char outString[256];
        memset(cmdString, 0, sizeof(cmdString));
        sprintf(cmdString, "nmcli dev wifi connect %s password %s", ssid, password);

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString) {
            return 0;
            }
        }
        return 0;
    }


    /**
     * @description: 重连
     * @param {type} 
     * @return: 
     */
    int wifi_reconnect(const char *ssid) {
        char cmdString[50];
        char outString[256];
        memset(cmdString, 0, sizeof(cmdString));
        sprintf(cmdString, "nmcli connect up %s", ssid);

        if (0 == popen_shell(cmdString, outString, sizeof(outString))) {
            if (NULL != outString) {
            return 0;
            }
        }
        return 0;
    }


    /**
     * @description: 连接wifi
     * @param {type} 
     * @return: 
     */
    int connect2wifi(const char *ssid, const char *passwd) {
        int ret = get_status();
        switch (ret) {
            case 0:return 0;
            case 1:
            case 3:
            {
                wifi_on_or_off(1);break;//开启

                //是否检测到该wifi
                if(0 != is_wifi_exists(ssid)){
                    return -1;
                }

                //当前是否持有这个wifi
                if(0 == is_wifi_use(ssid)){
                    wifi_reconnect(ssid);
                } else {
                    wifi_connect(ssid, passwd);
                }
            }
            break;

            case 2: break;
            default: return -1;
        }

        //是否已连接wifi
        if(0 == isConnectByNmcli()){
            return 0;
        } else {
            return -1;
        }
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
     * @description: 写文件
     * @param {type} 
     * @return: 
     */
    int write_file(const char *fileName, const char *data, int dataSize) {
        int ret = -1;
        int fd = open(fileName, O_WRONLY);
        if(fd > 0) {
            ret =write(fd, data, dataSize);
            close(fd);
        } else {
            printf("can not open %s\n", fileName);
        }
        return ret;
    }


    /**
     * @description: 是否连接到路由
     * @param {type} 
     * @return: 
     */
    void isConnect(const FunctionCallbackInfo<Value>& args) {
        //一个独立的V8执行环境
        Isolate* isolate = args.GetIsolate();
        HandleScope scope(isolate);

        int ret = isConnectByIfconfig();

        // 设置返回值
        args.GetReturnValue().Set(Number::New(isolate, ret));
    }


    /**
     * @description: 连接wifi
     * @param {type} 
     * @param {type}
     * @return: 
     */   
    void connect2wifi(const FunctionCallbackInfo<Value>& args) {
        // 使用 HandleScope 来管理生命周期
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);

        // 判断参数类型
        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        if (!args[0]->IsString() || !args[1]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        String::Utf8Value temp1(Local<String>::Cast(args[0]));
        std::string ssid = std::string(*temp1);

        String::Utf8Value temp2(Local<String>::Cast(args[1]));
        std::string passwd = std::string(*temp2);

        int value = connect2wifi(ssid.c_str(), passwd.c_str());
        if(0 == value) {
            char data[128];
            memset(data, 0, sizeof(data));
            sprintf(data, "{\"ssid\":\"%s\",\"passwd\":\"%s\"}", ssid.c_str(), passwd.c_str());
            write_file("", data, strlen(data));
        }

        // 声明
        Local<Number> num = Number::New(isolate, value);
        // 设置返回值
        args.GetReturnValue().Set(num);
    }


    /**
     * @description: 初始化函数(名字随便起)
     * @param {type} 
     * @return: 
     */
    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "isConnect", isConnect);
        NODE_SET_METHOD(exports, "connect2wifi", connect2wifi);
    }


    /**
     * @description: 导出初始化函数
     * @param {type} 
     * @return: 
     */
    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo
