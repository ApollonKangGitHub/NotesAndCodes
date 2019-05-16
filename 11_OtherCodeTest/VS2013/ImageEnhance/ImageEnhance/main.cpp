#include <iostream>
#include "cv.h"
#include "highgui.h"

#include "MSRCR.h"

using namespace cv;
using namespace std;

int main()
{
	vector<double> sigema;
	vector<double> weight;
	for (int i = 0; i < 3; i++)
		weight.push_back(1. / 3);
	// ����MSRCR.h�ж����˺�USE_EXTRA_SIGMA�����Դ˴���vector<double> sigema��û��ʲô����
	sigema.push_back(30);
	sigema.push_back(150);
	sigema.push_back(300);

	char key;
#if 0
	string path;
	cin >> path;
#endif
	Mat img, imgdst;
	Msrcr msrcr;
	img = imread("H:\\test5.jpg");//"H:\\test_MSRCR.jpg"
	imshow("Frame", img);
	
	msrcr.MultiScaleRetinexCR(img, imgdst, weight, sigema, 128, 128);
	imshow("MSRCR_dst", imgdst);

	msrcr.MultiScaleRetinex(img, imgdst, weight, sigema, 128, 128);
	imshow("MSR_dst", imgdst);

	double sigema_ssr = 30;
	msrcr.Retinex(img, imgdst, sigema_ssr, 128, 128);
	imshow("SSR_dst_30", imgdst);
#if 0
	sigema_ssr = 150;
	msrcr.Retinex(img, imgdst, sigema_ssr, 128, 128);
	imshow("SSR_dst_150", imgdst);

	sigema_ssr = 300;
	msrcr.Retinex(img, imgdst, sigema_ssr, 128, 128);
	imshow("SSR_dst_300", imgdst);
#endif
	key = (char)cvWaitKey(0);

	return 0;
}
