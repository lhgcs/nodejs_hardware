#include "test7.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace  cv;
using namespace  std;

void test7()
{
    Mat img = imread("/home/ubuntu/Desktop/demo/1.png");
    cvtColor(img,img,CV_BGR2GRAY);
    cout << img.channels() << endl;

    uint cnt[256]={0};
    float gailv[256]={0};

    int row = img.rows;
    int col = img.cols;

    //灰度值数量统计
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            uchar *p = img.ptr<uchar>(i);
            uchar temp = p[j];
            cnt[temp] =cnt[temp] + 1;
        }
    }

    //各灰度值所占的比例
    long long sum = row*col;
    for(int i=0;i<256;i++){
        gailv[i] = cnt[i]*1.0 /sum;
    }

    //绘直方图
    Mat dst = Mat::zeros(Size(256,200),CV_8UC3);
    for(int i=0;i<256;i++){
        line(dst, Point(i,200), Point(i,(uchar)(200-gailv[i]*100*10)), Scalar(0,0,255), 1, LINE_AA);
    }

    //累计概率
    for(int i=1;i<256;i++){
        gailv[i] = gailv[i] + gailv[i-1];
    }

    //直方图均衡化
    Mat dst2 = img.clone();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            uchar *p = dst2.ptr<uchar>(i);
            p[j] =(uchar)(256 *gailv[p[j]]);
        }
    }

    //API实现以上功能

    int histSize = 256;                    //直方图级数
    float range[] = { 0, 256 };
    const float *histRanges = { range };   //值域范围
    char channel = 1;                      //维数
    Mat mask;                              //mask
    Mat b_hist;                            //输出的直方图数据
    //直方图计算
    calcHist(&img, 1, NULL, mask, b_hist, channel, &histSize, &histRanges, true, false);

    int hist_h = 400;
    int hist_w = 512;
    int bin_w = hist_w / histSize;
    Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
    //归一化
    normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
        Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);
    }

    //进行直方图均衡化
    equalizeHist(img, dst);

    imshow("hist",histImage);

    imshow("dst",dst);
    imshow("dst2",dst2);
    waitKey(0);
}

