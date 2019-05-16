// OpenCV_1.cpp : �������̨Ӧ�ó������ڵ㡣
//
//�ʺ�ͼ����ɫ����ȡһ��ֵ
// R G B gray
//----------------------------------
// �� 255, 0, 0 255
// �� 255, 127, 0 204
// �� 255, 255, 0 153
// �� 0, 255, 0 102
// �� 0, 255, 255 51
// �� 0, 0, 255 0

//#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

int main(int argc, char * argv[])
{
   Mat img = imread("F:\\2.jpg", CV_LOAD_IMAGE_GRAYSCALE);//���ûҶȸ�ʽ��ȡͼƬ
   namedWindow("bmp_img", CV_WINDOW_NORMAL);
   imshow("bmp_img", img);
   imwrite("gray.jpg", img);
#if 1
	Mat img_pseudo_color(img.rows, img.cols, CV_8UC3);//����RGBͼ�񣬲���CV_8UC3�̳��ĵ������н���

	int tmp=0;

	for (int hang = 0; hang<img.rows; hang++)//תΪα��ɫͼ��ľ����㷨
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
	Mat img_rain_bow_color(img.rows, img.cols, CV_8UC3);//����RGBͼ��
#define IMG_B(img,y,x) img.at<Vec3b >(y,x)[0]
#define IMG_G(img,y,x) img.at<Vec3b>(y,x)[1]
#define IMG_R(img,y,x) img.at<Vec3b>(y,x)[2]
	uchar tmp2=0;
	for (int y=0;y<img.rows;y++)//תΪ�ʺ�ͼ�ľ����㷨����Ҫ˼·�ǰѻҶ�ͼ��Ӧ��0��255����ֵ�ֱ�ת���ɲʺ�ɫ���졢�ȡ��ơ��̡��ࡢ����
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