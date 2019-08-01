#include "test6.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

void test6()
{
    Mat img = imread("/home/ubuntu/Desktop/demo/1.png");
    Mat out;

    //卷积的边界：边缘像素没有和锚点重合，处理前增加边缘像素,，处理后去掉
    copyMakeBorder(img, img, 20, 20, 20, 20, BORDER_CONSTANT, Scalar(0,0,255));
    imshow("img",img);

    //边缘检测
    //Canny算子
    Canny(img, out, 3, 9,3 );
    imshow("Canny",out);
    cout << out.channels() << endl;//单通道灰度

    Mat outX,outY,outXAbs,outYAbs;
    //X方向梯度
    Sobel(img, outX, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
    convertScaleAbs(outX, outXAbs);
    //Y方向梯度
    Sobel(img, outY, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
    //计算绝对值，并将结果转换成8位
    convertScaleAbs(outY, outYAbs);
    //合并梯度(近似)
    addWeighted(outXAbs, 0.5, outYAbs, 0.5, 0, out);
    imshow("x",outXAbs);
    imshow("y",outYAbs);
    imshow("Sobel",out);
    cout << out.channels() << endl;//3通道灰度

    Mat temp;
    //Laplace函数
    Laplacian(img, temp, CV_16S, 3, 1, 0, BORDER_DEFAULT );
    convertScaleAbs(temp, out);
    imshow("Laplacian",out);
    cout << out.channels() << endl;//3通道灰度

    //X方向梯度
    Scharr(img, outX, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
    convertScaleAbs(outX, outXAbs);
    //Y方向梯度
    Scharr(img, outY, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
    convertScaleAbs(outY, outYAbs);
    //合并梯度
    addWeighted(outXAbs, 0.5, outYAbs, 0.5, 0, out);
    imshow("x",outXAbs);
    imshow("y",outYAbs);
    imshow("Scharr",out);
    cout << out.channels() << endl;//3通道灰度

    //霍夫线性变换
    cvtColor(out, out, COLOR_BGR2GRAY);//转化边缘检测后的图为灰度图
    cout << out.channels() << endl;    //3通道灰度

    Mat dstImage = out.clone();
    vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
    int step =1;        //扫描步长
    int thresh = 150;   //阈值，获取足够焦点的极坐标
    HoughLines(out, lines, step, CV_PI / 180, thresh, 0, 0);
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0];   // 极坐标中的r长度
        float theta = lines[i][1]; // 极坐标中的角度
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        //转换为平面坐标的四个点
        //依次在图中绘制出每条线段
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dstImage, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
        //Vec4f hline = plines[i];
        //line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, );
    }

    //霍夫圆检测
    vector<Vec3f> pcircles;//输出结果
    double mindist = 10;   //最短距离
    int minradius = 100;   //最小半径
    int maxradius = 300;   //最大半径
    double centerRange = 10; //中心点累加器阈值 – 候选圆心

    HoughCircles(out, pcircles, CV_HOUGH_GRADIENT, 1, mindist, 100, centerRange, minradius, maxradius);
    for (size_t i = 0; i < pcircles.size(); i++) {
        Vec3f cc = pcircles[i];
        //绘制圆心
        Point center(cc[0], cc[1]);
        //绘制圆心
        circle(out, center,     2, Scalar(0,0,255), 2, LINE_AA);
        //绘制圆轮廓
        circle(out, center, cc[2], Scalar(0, 0, 255), 2, LINE_AA);
    }

    vector < vector<Point> > contours;
    vector<Vec4i> hierachy;

    //findContours(out, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    Mat dst = Mat::zeros(out.size(), CV_8UC3);
    RNG rng(12345);
    for (size_t i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(dst, contours, i, color, 2, 8, hierachy, 0, Point(0, 0));
    }
    imshow("dst",dst);
    imshow("out",out);
    waitKey(0);
}

