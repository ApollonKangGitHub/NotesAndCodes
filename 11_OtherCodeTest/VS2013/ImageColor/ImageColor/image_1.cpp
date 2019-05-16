// OpenCV_1.cpp : 定义控制台应用程序的入口点。
//
//彩虹图的颜色分配取一下值
// R G B gray
//----------------------------------
// 红 255, 0, 0 255
// 橙 255, 127, 0 204
// 黄 255, 255, 0 153
// 绿 0, 255, 0 102
// 青 0, 255, 255 51
// 蓝 0, 0, 255 0

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

int main(int argc, char * argv[])
{
   Mat img = imread("F:\\2.jpg", CV_LOAD_IMAGE_GRAYSCALE);//采用灰度格式读取图片
   namedWindow("bmp_img", CV_WINDOW_NORMAL);
   imshow("bmp_img", img);
   imwrite("gray.jpg", img);
#if 1
	Mat img_pseudo_color(img.rows, img.cols, CV_8UC3);//构造RGB图像，参数CV_8UC3教程文档里面有讲解

	int tmp=0;

	for (int hang = 0; hang<img.rows; hang++)//转为伪彩色图像的具体算法
	{
		for (int lie = 0; lie < img.cols; lie++)
		{
			tmp = img.at<unsigned char>(hang, lie);
			img_pseudo_color.at<Vec3b>(hang, lie)[0] = abs(255 - tmp);  //red
			img_pseudo_color.at<Vec3b>(hang, lie)[1] = abs(127 - tmp);
			img_pseudo_color.at<Vec3b>(hang, lie)[2] = abs(0 - tmp);
		}
	}

	namedWindow("img_pseudo_color", CV_WINDOW_NORMAL);
	imshow("img_pseudo_color", img_pseudo_color);
#endif

#if 1
	Mat img_rain_bow_color(img.rows, img.cols, CV_8UC3);//构造RGB图像
#define IMG_B(img,y,x) img.at<Vec3b >(y,x)[0]
#define IMG_G(img,y,x) img.at<Vec3b>(y,x)[1]
#define IMG_R(img,y,x) img.at<Vec3b>(y,x)[2]
	uchar tmp2=0;
	for (int y=0;y<img.rows;y++)//转为彩虹图的具体算法，主要思路是把灰度图对应的0～255的数值分别转换成彩虹色：红、橙、黄、绿、青、蓝。
	{
		for (int x=0;x<img.cols;x++)
		{
			tmp2 = img.at<uchar>(y,x);
			if (tmp2 <= 51)
			{
				IMG_B(img_rain_bow_color,y,x) = 255;
				IMG_G(img_rain_bow_color,y,x) = tmp2*5;
				IMG_R(img_rain_bow_color,y,x) = 0;
			}
			else if (tmp2 <= 102)
			{
				tmp2-=51;
				IMG_B(img_rain_bow_color,y,x) = 255-tmp2*5;
				IMG_G(img_rain_bow_color,y,x) = 255;
				IMG_R(img_rain_bow_color,y,x) = 0;
			}
			else if (tmp2 <= 153)
			{
				tmp2-=102;
				IMG_B(img_rain_bow_color,y,x) = 0;
				IMG_G(img_rain_bow_color,y,x) = 255;
				IMG_R(img_rain_bow_color,y,x) = tmp2*5;
			}
			else if (tmp2 <= 204)
			{
				tmp2-=153;
				IMG_B(img_rain_bow_color,y,x) = 0;
				IMG_G(img_rain_bow_color,y,x) = 255-uchar(128.0*tmp2/51.0+0.5);
				IMG_R(img_rain_bow_color,y,x) = 255;
			}
			else
			{
				tmp2-=204;
				IMG_B(img_rain_bow_color,y,x) = 0;
				IMG_G(img_rain_bow_color,y,x) = 127-uchar(127.0*tmp2/51.0+0.5);
				IMG_R(img_rain_bow_color,y,x) = 255;
			}
		}
	}
	namedWindow("img_rain_bow_color", CV_WINDOW_NORMAL);
	imshow("img_rain_bow_color", img_rain_bow_color);
#endif  
   
	waitKey(0);
	destroyAllWindows();
	return 0;
}