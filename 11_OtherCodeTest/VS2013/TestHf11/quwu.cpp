#include "StdAfx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include<iostream>
#include "quwu.h"

using namespace std;

char tbarname1[] = "调节block";
//定义两个滑动条,用于调节参数
char tbarname2[] = "调节w";
//w是为了保留一部分的雾

int block=5;
int w1=80;
double w;

IplImage *src=NULL;
IplImage *dst=NULL;

//定义去雾函数如下
IplImage *quw(CString srcFile,int block,double w)
{
//图像分别有三个颜色通道
         IplImage *dst1=NULL;
         IplImage *dst2=NULL;
         IplImage *dst3=NULL;
         IplImage *imgroi1;

         //dst1的ROI
         IplImage *imgroi2;
         //dst2的ROI
         IplImage *imgroi3;
         //dst3的ROI
         IplImage *roidark;
         //dark channel的ROI

         IplImage *dark_channel=NULL;
         //暗原色先验的指针
         IplImage *toushelv=NULL;
         //透射率
//去雾算法运算后的三个通道
         IplImage *j1=NULL;
         IplImage *j2=NULL;
         IplImage *j3=NULL;
//去雾后的图像,三通道合并成
         IplImage *dst=NULL;
//源图像ROI位置以及大小
         CvRect ROI_rect; 
//分离的三个通道

		 src=cvLoadImage(srcFile,-1);

         dst1=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         dst2=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         dst3=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);

 //为各个ROI分配内存
         imgroi1=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         imgroi2=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         imgroi3=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         roidark=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
//为j1 j2 j3分配大小
         j1=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         j2=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         j3=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//为暗原色先验指针分配大小
         dark_channel=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//为透射率指针分配大小
         toushelv=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//dst分配大小
         dst=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3);
//将原彩色图像分离成三通道
         cvSplit(src,dst1,dst2,dst3,NULL);
//求暗原色
         ROI_rect.width=block;
         ROI_rect.height=block;
         ROI_rect.x=0;
         ROI_rect.y=0; 
         int i;
         int j;
         double min1=0;
         double max1=0;
         double min2=0;
         double max2=0;
         double min3=0;
         double max3=0;
         double min=0;
         CvScalar value;
         for(i=0;i<src->width/block;i++)
         {        for(j=0;j<src->height/block;j++)
                   {
                            //分别计算三个通道内ROI的最小值
                            cvSetImageROI(dst1,ROI_rect);
                            cvCopy(dst1,imgroi1,NULL);
                            cvMinMaxLoc(imgroi1,&min1,&max1,NULL,NULL);
                            cvSetImageROI(dst2,ROI_rect);
                            cvCopy(dst2,imgroi2,NULL);
                            cvMinMaxLoc(imgroi2,&min2,&max2,NULL,NULL);
                            cvSetImageROI(dst3,ROI_rect);
                            cvCopy(dst3,imgroi3,NULL);
                            cvMinMaxLoc(imgroi3,&min3,&max3,NULL,NULL);
                            //求三个通道内最小值的最小值
                            if(min1<min2)
                                     min=min1;
                            else
                                     min=min2;
                            if(min>min3)
                                     min=min3;//min为这个ROI中暗原色
                            value=cvScalar(min,min,min,min);//min放在value中
                            //min赋予dark_channel中相应的ROI
                            cvSetImageROI(dark_channel,ROI_rect);
                            cvSet(roidark,value,NULL);
                            cvCopy(roidark,dark_channel,NULL);
                            //释放各个ROI
                            cvResetImageROI(dst1);
                            cvResetImageROI(dst2);
                            cvResetImageROI(dst3);
                            cvResetImageROI(dark_channel);
                            //转入下一个ROI
                            ROI_rect.x=block*i;
                            ROI_rect.y=block*j;
                   }
         }

         //保存暗原色先验的图像
         cvSaveImage("f:/dark_channel_prior.jpg",dark_channel);
//利用得到的暗原色先验dark_channel_prior.jpg求大气光强
         double min_dark;
         double max_dark;
         CvPoint min_loc;
         CvPoint max_loc;//max_loc是暗原色先验最亮一小块的原坐标
         cvMinMaxLoc(dark_channel,&min_dark,&max_dark,&min_loc,&max_loc,NULL);
         cout<<max_loc.x<<" "<<max_loc.y<<endl;
         ROI_rect.x=max_loc.x;
         ROI_rect.y=max_loc.y;
         double A_dst1;//定义大气光成分的估计值
         double dst1_min;
         double A_dst2;
         double dst2_min;
         double A_dst3;
         double dst3_min;
         cvSetImageROI(dst1,ROI_rect);
//按照论文方法求大气光强估计值
         cvCopy(dst1,imgroi1,NULL);
         cvMinMaxLoc(imgroi1,&dst1_min,&A_dst1,NULL,NULL);
         cvSetImageROI(dst2,ROI_rect);
         cvCopy(dst2,imgroi2,NULL);
         cvMinMaxLoc(imgroi2,&dst2_min,&A_dst2,NULL,NULL);
         cvSetImageROI(dst3,ROI_rect);
         cvCopy(dst3,imgroi3,NULL);
         cvMinMaxLoc(imgroi3,&dst3_min,&A_dst3,NULL,NULL);
         cout<<A_dst1<<" "<<A_dst2<<" "<<A_dst3<<endl;//这三值为大气光强度估计值
//求透射率
         int k;
         int l;
         CvScalar m;
         CvScalar n;//暗原色先验各元素值
         for(k=0;k<src->height;k++)
         {
                   for(l=0;l<src->width;l++)
                   {
                            m=cvGet2D(dark_channel,k,l);
                            n=cvScalar(255-w*m.val[0]);
                            //w目的是保留一部分的雾,使图像看起来真实些
                            cvSet2D(toushelv,k,l,n);
                   }
         }
         cvSaveImage("f:/toushelv.jpg",toushelv);
 
//求无雾图像
         int p,q;
         double tx;
         double jj1,jj2,jj3;
         CvScalar ix,jx;
         for(p=0;p<src->height;p++)
         {
                   for(q=0;q<src->width;q++)
                   {
                            tx=cvGetReal2D(toushelv,p,q);
                            tx=tx/255;
                            if(tx<0.1)
                                     tx=0.1;
                            ix=cvGet2D(src,p,q);
                            jj1=(ix.val[0]-A_dst1)/tx+A_dst1;//根据雾产生模型运算,还原出无雾图像
                            jj2=(ix.val[1]-A_dst2)/tx+A_dst2;
                            jj3=(ix.val[2]-A_dst3)/tx+A_dst3;
                            jx=cvScalar(jj1,jj2,jj3,0.0);
                            cvSet2D(dst,p,q,jx);
                   }
         }
         cvSaveImage(DES_FILE,dst);

//释放指针
         cvReleaseImage(&dst1);
         cvReleaseImage(&dst2);
         cvReleaseImage(&dst3);
         cvReleaseImage(&imgroi1);
         cvReleaseImage(&imgroi2);
         cvReleaseImage(&imgroi3);         
	 cvReleaseImage(&roidark);
         cvReleaseImage(&dark_channel);
         cvReleaseImage(&toushelv);
         cvReleaseImage(&j1);
         cvReleaseImage(&j2);
         cvReleaseImage(&j3);
         return dst;

}
#if 0

void on_trackbar1(int h)

{
	
	dst=quw(src,block,w);
	
	cvShowImage("目的图像",dst);
	
	//      cvWaitKey(0);
	
}

void on_trackbar2(int h)

{
	
	
	
	w=(double)w1/100;
	
	dst=quw(src,block,w);
	
	cvShowImage("目的图像",dst);
	
	//      cvWaitKey(0);
	
}

//主函数如下

void main()

{
	
	//打开图像
	
	src=cvLoadImage("8.jpg",-1);
	
	//创造窗口
	
	cvNamedWindow("有雾图像",CV_WINDOW_AUTOSIZE);
	
	cvShowImage("有雾图像",src);
	
	cvNamedWindow("目的图像",CV_WINDOW_AUTOSIZE);
	
	cvCreateTrackbar(tbarname1, "目的图像", &block, 15, on_trackbar1);
	
	cvCreateTrackbar(tbarname2, "目的图像", &w1, 100, on_trackbar2);
	
	cvWaitKey(0);
	
	cvReleaseImage(&src);
	
	cvReleaseImage(&dst);
	
}
#endif
