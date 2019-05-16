#include "StdAfx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include<iostream>
#include "quwu.h"

using namespace std;

char tbarname1[] = "����block";
//��������������,���ڵ��ڲ���
char tbarname2[] = "����w";
//w��Ϊ�˱���һ���ֵ���

int block=5;
int w1=80;
double w;

IplImage *src=NULL;
IplImage *dst=NULL;

//����ȥ��������
IplImage *quw(CString srcFile,int block,double w)
{
//ͼ��ֱ���������ɫͨ��
         IplImage *dst1=NULL;
         IplImage *dst2=NULL;
         IplImage *dst3=NULL;
         IplImage *imgroi1;

         //dst1��ROI
         IplImage *imgroi2;
         //dst2��ROI
         IplImage *imgroi3;
         //dst3��ROI
         IplImage *roidark;
         //dark channel��ROI

         IplImage *dark_channel=NULL;
         //��ԭɫ�����ָ��
         IplImage *toushelv=NULL;
         //͸����
//ȥ���㷨����������ͨ��
         IplImage *j1=NULL;
         IplImage *j2=NULL;
         IplImage *j3=NULL;
//ȥ����ͼ��,��ͨ���ϲ���
         IplImage *dst=NULL;
//Դͼ��ROIλ���Լ���С
         CvRect ROI_rect; 
//���������ͨ��

		 src=cvLoadImage(srcFile,-1);

         dst1=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         dst2=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         dst3=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);

 //Ϊ����ROI�����ڴ�
         imgroi1=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         imgroi2=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         imgroi3=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
         roidark=cvCreateImage(cvSize(block,block),IPL_DEPTH_8U,1);
//Ϊj1 j2 j3�����С
         j1=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         j2=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
         j3=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//Ϊ��ԭɫ����ָ������С
         dark_channel=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//Ϊ͸����ָ������С
         toushelv=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
//dst�����С
         dst=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3);
//��ԭ��ɫͼ��������ͨ��
         cvSplit(src,dst1,dst2,dst3,NULL);
//��ԭɫ
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
                            //�ֱ��������ͨ����ROI����Сֵ
                            cvSetImageROI(dst1,ROI_rect);
                            cvCopy(dst1,imgroi1,NULL);
                            cvMinMaxLoc(imgroi1,&min1,&max1,NULL,NULL);
                            cvSetImageROI(dst2,ROI_rect);
                            cvCopy(dst2,imgroi2,NULL);
                            cvMinMaxLoc(imgroi2,&min2,&max2,NULL,NULL);
                            cvSetImageROI(dst3,ROI_rect);
                            cvCopy(dst3,imgroi3,NULL);
                            cvMinMaxLoc(imgroi3,&min3,&max3,NULL,NULL);
                            //������ͨ������Сֵ����Сֵ
                            if(min1<min2)
                                     min=min1;
                            else
                                     min=min2;
                            if(min>min3)
                                     min=min3;//minΪ���ROI�а�ԭɫ
                            value=cvScalar(min,min,min,min);//min����value��
                            //min����dark_channel����Ӧ��ROI
                            cvSetImageROI(dark_channel,ROI_rect);
                            cvSet(roidark,value,NULL);
                            cvCopy(roidark,dark_channel,NULL);
                            //�ͷŸ���ROI
                            cvResetImageROI(dst1);
                            cvResetImageROI(dst2);
                            cvResetImageROI(dst3);
                            cvResetImageROI(dark_channel);
                            //ת����һ��ROI
                            ROI_rect.x=block*i;
                            ROI_rect.y=block*j;
                   }
         }

         //���氵ԭɫ�����ͼ��
         cvSaveImage("f:/dark_channel_prior.jpg",dark_channel);
//���õõ��İ�ԭɫ����dark_channel_prior.jpg�������ǿ
         double min_dark;
         double max_dark;
         CvPoint min_loc;
         CvPoint max_loc;//max_loc�ǰ�ԭɫ��������һС���ԭ����
         cvMinMaxLoc(dark_channel,&min_dark,&max_dark,&min_loc,&max_loc,NULL);
         cout<<max_loc.x<<" "<<max_loc.y<<endl;
         ROI_rect.x=max_loc.x;
         ROI_rect.y=max_loc.y;
         double A_dst1;//���������ɷֵĹ���ֵ
         double dst1_min;
         double A_dst2;
         double dst2_min;
         double A_dst3;
         double dst3_min;
         cvSetImageROI(dst1,ROI_rect);
//�������ķ����������ǿ����ֵ
         cvCopy(dst1,imgroi1,NULL);
         cvMinMaxLoc(imgroi1,&dst1_min,&A_dst1,NULL,NULL);
         cvSetImageROI(dst2,ROI_rect);
         cvCopy(dst2,imgroi2,NULL);
         cvMinMaxLoc(imgroi2,&dst2_min,&A_dst2,NULL,NULL);
         cvSetImageROI(dst3,ROI_rect);
         cvCopy(dst3,imgroi3,NULL);
         cvMinMaxLoc(imgroi3,&dst3_min,&A_dst3,NULL,NULL);
         cout<<A_dst1<<" "<<A_dst2<<" "<<A_dst3<<endl;//����ֵΪ������ǿ�ȹ���ֵ
//��͸����
         int k;
         int l;
         CvScalar m;
         CvScalar n;//��ԭɫ�����Ԫ��ֵ
         for(k=0;k<src->height;k++)
         {
                   for(l=0;l<src->width;l++)
                   {
                            m=cvGet2D(dark_channel,k,l);
                            n=cvScalar(255-w*m.val[0]);
                            //wĿ���Ǳ���һ���ֵ���,ʹͼ��������ʵЩ
                            cvSet2D(toushelv,k,l,n);
                   }
         }
         cvSaveImage("f:/toushelv.jpg",toushelv);
 
//������ͼ��
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
                            jj1=(ix.val[0]-A_dst1)/tx+A_dst1;//���������ģ������,��ԭ������ͼ��
                            jj2=(ix.val[1]-A_dst2)/tx+A_dst2;
                            jj3=(ix.val[2]-A_dst3)/tx+A_dst3;
                            jx=cvScalar(jj1,jj2,jj3,0.0);
                            cvSet2D(dst,p,q,jx);
                   }
         }
         cvSaveImage(DES_FILE,dst);

//�ͷ�ָ��
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
	
	cvShowImage("Ŀ��ͼ��",dst);
	
	//      cvWaitKey(0);
	
}

void on_trackbar2(int h)

{
	
	
	
	w=(double)w1/100;
	
	dst=quw(src,block,w);
	
	cvShowImage("Ŀ��ͼ��",dst);
	
	//      cvWaitKey(0);
	
}

//����������

void main()

{
	
	//��ͼ��
	
	src=cvLoadImage("8.jpg",-1);
	
	//���촰��
	
	cvNamedWindow("����ͼ��",CV_WINDOW_AUTOSIZE);
	
	cvShowImage("����ͼ��",src);
	
	cvNamedWindow("Ŀ��ͼ��",CV_WINDOW_AUTOSIZE);
	
	cvCreateTrackbar(tbarname1, "Ŀ��ͼ��", &block, 15, on_trackbar1);
	
	cvCreateTrackbar(tbarname2, "Ŀ��ͼ��", &w1, 100, on_trackbar2);
	
	cvWaitKey(0);
	
	cvReleaseImage(&src);
	
	cvReleaseImage(&dst);
	
}
#endif
