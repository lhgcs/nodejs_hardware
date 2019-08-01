#include "test1.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

static void get_img_info(Mat &img){
    int row = img.rows;           //行数
    int col = img.cols;           //列数
    int channel = img.channels(); //通道数
    int deep = img.depth();       //深度
    cout << "row:" << row << " col:" << col << " channel:" << channel << " deep:" << deep << endl;
}

void test1()
{
    //图像读取
    Mat img          = imread("/home/ubuntu/Desktop/demo/1.png");     //3通道 彩色
    Mat img_unchange = imread("/home/ubuntu/Desktop/demo/1.png", -1); //4通道 彩色
    Mat img_gray     = imread("/home/ubuntu/Desktop/demo/1.png", 0);  //1通道 灰度
    Mat img_color    = imread("/home/ubuntu/Desktop/demo/1.png", 1);  //3通道 彩色

    if(img.empty()){
        cout << "图像加载失败！"<< endl;
        return;
    }

    //创建窗口
    //CV_WINDOW_AUTOSIZE窗口根据图像大小
    namedWindow("img", CV_WINDOW_AUTOSIZE);
    //在窗中显示图片
    imshow("img", img);

    imshow("img_unchange", img_unchange);
    imshow("img_gray", img_gray);
    imshow("img_color", img_color);

    get_img_info(img);
    get_img_info(img_unchange);
    get_img_info(img_gray);
    get_img_info(img_color);

    //保存图片
    vector<int> v=vector<int>(CV_IMWRITE_PNG_COMPRESSION,5);
    imwrite("/home/ubuntu/Desktop/demo/2.png", img, v);

    //等待有按键按下
    int key = waitKey(0);
    cout << "key:" << key << endl;
    //销毁窗口
    destroyWindow("img");
    //销毁所有窗口
    destroyAllWindows();
}
