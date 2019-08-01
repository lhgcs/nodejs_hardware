#include "test3.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

void test3()
{


    Mat img = imread("/home/ubuntu/Desktop/demo/1.png");
    //图像复制
    Mat img2 = img.clone();
    //img.copyTo(img2);
    Mat img3;
    vector<Mat> channels;
    //3通道图像转换成3个单通道图像
    split(img,channels);
    //3个单通道重新合并成一个3通道
    merge(channels,img3);
    imshow("b",channels[0]);
    imshow("g",channels[1]);
    imshow("r",channels[2]);

    imshow("img",img);
    imshow("img2",img2);
    imshow("img3",img3);

    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    Mat img_gray = Mat(row,col,img.type());

    for(int i=0; i<row; i++){
        for(int j=0; j<col * channel; j+=3){
             //像素值求均值
             uchar temp = (0.0+img.ptr<uchar>(i)[j] + img.ptr<uchar>(i)[j+1] + img.ptr<uchar>(i)[j+2])/3;
             //像素范围  value<0 返回0  value>255 返回255
             img_gray.ptr<uchar>(i)[j] = saturate_cast<uchar>(temp);
             img_gray.ptr<uchar>(i)[j+1] = saturate_cast<uchar>(temp);
             img_gray.ptr<uchar>(i)[j+2] = saturate_cast<uchar>(temp);
        }
    }

    //转换为灰度
    //cvtColor(img, img_gray, CV_BGR2GRAY);
    imshow("img_gray",img_gray);

    //400*400 4通道图像
    Mat dst = Mat(400,400,CV_8UC4,Scalar(255,0,0,255));

    Point point1 = Point(0,0);
    Point point2 = Point(dst.rows/2, dst.cols/2);

    int width = 5;
    Scalar color = Scalar(0, 0, 255);
    //线段
    line(dst, point1, point2, color, width, LINE_AA);
    //矩形
    rectangle(dst, Rect(0,0,100,100), color, width, LINE_8);
    //椭圆
    ellipse(dst, point2, Size(100,100), 0,0,300, color, width, LINE_8);//顺时针
    //圆
    circle(dst, point2, dst.rows/2, color, width,8);
    //多边形
    Point pts[1][4];
    pts[0][0] = Point(100, 100);
    pts[0][1] = Point(150, 200);
    pts[0][2] = Point(100, 200);
    pts[0][3] = Point(0, 100);

    const Point* ppts[] = { pts[0] };
    //连接4个点
    int npt[] = { 4 };
    fillPoly(dst, ppts, npt, 1, color, LINE_8);
    //文字
    putText(dst, "Hello OpenCV", point2, CV_FONT_HERSHEY_COMPLEX, 4.0, color, 1, LINE_8);//字体左下角

    imshow("dst",dst);
    waitKey(0);
}

