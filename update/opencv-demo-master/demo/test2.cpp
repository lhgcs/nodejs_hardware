#include "test2.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;


static void get_img_info(Mat &img){
    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    int deep = img.depth();
    cout << "row:" << row << " col:" << col << " channel:" << channel << " deep:" << deep << endl;
}

void test2()
{
    /*
    图像本质上：二维矩阵,值是0-255像素值
    图像处理本质：对图像的矩阵操作
    3*3 像素的3通道的图像
    得到3行9列的数组
    */
    Mat dst = Mat::zeros(Size(3,3), CV_8UC3);
    get_img_info(dst);
    cout << dst << endl;

    /*
    3*3 像素的1通道的图像
    得到3行3列的数组
    */
    dst = Mat::zeros(Size(3,3), CV_8UC1);
    get_img_info(dst);
    cout << dst << endl;

    dst = Mat::ones(Size(30,30), CV_32FC3);//3通道float
    get_img_info(dst);
    cout << dst << endl;

    int row = dst.rows;
    int col = dst.cols;
    int channel = dst.channels();

    for(int i=0; i<row; i++){
       for(int j=0; j<col * channel; j++){
            //获取图像像素指针
            float* cur = dst.ptr<float>(i);            //第i行
            //像素范围  <0 返回0  value>255 返回255
            cur[j] = saturate_cast<float>(cur[j] * 2);//元素值*0.5   修改元素值
       }
    }

    imshow("img1",dst);

    for(int i=0; i<row; i++){
       for(int j=0; j<col; j++){
            //动态地址运算配合at
            for(int k=0; k<channel; k++){
                dst.at<Vec3f>(i,j)[k] = (dst.at<Vec3f>(i,j)[k] * 2);
            }
       }
    }

    imshow("img2",dst);

    //获取迭代器
    Mat_<Vec3f>::iterator it = dst.begin<Vec3f>();  //初始位置的迭代器
    Mat_<Vec3f>::iterator itend = dst.end<Vec3f>();  //终止位置的迭代器

    //存取彩色图像像素
    for(;it != itend;++it)  {
       for(int k=0; k<channel; k++){
           (*it)[k] = (*it)[k] * 2;
       }
    }
    imshow("img3",dst);


    //等待直到有键按下
    int key = waitKey(0);
    cout << "key:" << key << endl;
}



