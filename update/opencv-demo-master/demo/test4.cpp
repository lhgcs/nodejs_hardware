#include "test4.h"


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

//滚动条的回调函数
void on_Trackbar(int value, void*){
    //滚动条值
    cout << value << endl;
}

//鼠标回调函数（只在绑定窗口中有效）
void on_MouseHandle(int event, int x, int y, int flags, void* param){
    switch(event){
        //鼠标移动,只要鼠标有移动就触发
        case EVENT_MOUSEMOVE:{
            cout << "move" << endl;
        }
        break;

        //左键按下，按下时触发一次
        case EVENT_LBUTTONDOWN:{
            cout << "down" << endl;
        }
        break;
        //左键抬起
        case EVENT_LBUTTONUP:{
            cout << "up" << endl;
        }
        break;
    }
    cout << "x:" << x << " y:" << y << " flag:" << flags << endl;
    switch (flags) {
        case 0:cout << "no" << endl;break;
        case 1:cout << "left" << endl;break;
        case 2:cout << "right" << endl;break;
        case 4:cout << "滚轮" << endl;break;
        default:break;
    }
}


#define NAME "src"
void test4()
{
    Mat src = imread("/home/ubuntu/Desktop/demo/1.png");     //3通道 彩色
    double timeStart = static_cast<double>(getTickCount());

    double timeEnd = static_cast<double>(getTickCount());
    cout<<"时间为： "<< (timeEnd - timeStart) / getTickFrequency()  <<"秒"<<endl;
    //创建窗体，必须先创建窗口再绑定
    namedWindow(NAME, WINDOW_AUTOSIZE);

    //滑动条初值
    int trackValue = 50;
    int maxValue = 100;
    //滑动条控件
    createTrackbar("track", NAME, &trackValue, maxValue, on_Trackbar);

    //结果在回调函数中显示
    on_Trackbar(trackValue, 0);
    setMouseCallback(NAME, on_MouseHandle, (void*)&src);

    imshow(NAME, src);
    waitKey(0);
}

