#include "test5.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

void test5()
{
    Mat img = imread("/home/ubuntu/Desktop/demo/1.png");

    //必须是奇数，值越大图像越模糊
    Size s = Size(15,15);//降噪
    Mat out;
    //方框滤波
    boxFilter(img, out, -1, s);
    imshow("boxFilter",out);

    //均值滤波
    blur(img, out, s);
    imshow("blur",out);

    //进行高斯滤波操作
    GaussianBlur(img, out, s, 0, 0 );
    imshow("GaussianBlur",out);

    //进行中值滤波操作
    medianBlur(img, out, 7);
    imshow("medianBlur",out);

    //进行双边滤波操作
    bilateralFilter(img, out, 25, 25*2, 25/2 );
    imshow("bilateralFilter",out);

    //定义核
    Mat element = getStructuringElement(MORPH_RECT, s);
    //膨胀
    dilate(img, out, element);
    imshow("dilate",out);
    //腐蚀
    erode(img, out, element);
    imshow("erode",out);
    //开运算
    morphologyEx(img, out, MORPH_OPEN, element);
    imshow("morphologyEx",out);
    /*
        MORPH_DILATE     膨胀
        MORPH_ERODE      腐蚀
        MORPH_OPEN       开运算
        MORPH_CLOSE      闭运算
        MORPH_GRADIENT   梯度
        MORPH_TOPHAT     顶帽运算
        MORPH_BLACKHAT   黑帽运算
    */

    //向上取样    放大只能是2倍
    pyrUp(img, out, Size(img.cols*2, img.rows*2));
    imshow("pyrUp",out);
    //向下取样   只能是2倍
    pyrDown(img, out, Size(img.cols/2, img.rows/2));
    imshow("pyrDown",out);

    //DOG高斯不同
    Mat out1,out2;
    cvtColor(img, img, CV_BGR2GRAY);
    //进行高斯滤波操作
    GaussianBlur(img, out1, Size(5, 5), 0, 0 );
    GaussianBlur(img, out2, Size(15, 15), 0, 0 );
    subtract(out1, out2, out, Mat());

    // 归一化显示
    normalize(out, out, 255, 0, NORM_MINMAX);
    imshow("dst",out);

    //调用阈值函数
    Mat dst2;
    threshold(img, dst2, 100, 255, THRESH_TRIANGLE);

    waitKey(0);
    destroyAllWindows();
}

