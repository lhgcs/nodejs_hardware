/*
 * @Description: hello world
 * @Author: your name
 * @Date: 2019-07-17 16:23:59
 * @LastEditTime: 2019-07-24 10:33:38
 * @LastEditors: Please set LastEditors
 */

/*

文件应用两个头部node.h和v8.h，整体结构和node的module非常相似，都是先定义Function/Object，然后export。
编译：
node-gyp configure  //生成项目相应的平台，生产build目录和Makefile文件
node-gyp build      //编译成二进制 xxx.node文件
*/

#include <node.h>
#include <v8.h>

using namespace v8;

// 传入了两个参数，args[0] 字符串，args[1] 回调函数
void hello(const FunctionCallbackInfo<Value>& args) {
  // 使用 HandleScope 来管理生命周期
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  // 判断参数格式和格式
  if (args.Length() < 2 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // callback, 使用Cast方法来转换
  Local<Function> callback = Local<Function>::Cast(args[1]);
  Local<Value> argv[1] = {
    // 拼接String
    String::Concat(Local<String>::Cast(args[0]), String::NewFromUtf8(isolate, " world"))
  };
  // 调用回调, 参数: 当前上下文，参数个数，参数列表
  callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);
}

// 相当于在 exports 对象中添加 { hello: hello }
void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", hello);
}

// 将 export 对象暴露出去
// 原型 `NODE_MODULE(module_name, Initialize)`
NODE_MODULE(hello, init);
