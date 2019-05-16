#include "MSRCR.h"

/*===========================================================
* ����: CreateKernel
* ˵��������һ����׼����һά��˹�ˣ�
* ������
*   double sigma: ��˹�˱�׼ƫ��
* ����ֵ��
*   double*: ����Ϊ((6*sigma)/2) * 2 + 1��double����
* ע��
*   ��������Ҫɾ�����ںˣ�
* --------------------------------------------------------
*  Summary:
*  Creates a normalized 1 dimensional gaussian kernel.
*
*  Arguments:
*  double sigma - the standard deviation of the gaussian kernel.
*
*  Returns:
*  vector<double> - an vector of values of length ((6*sigma)/2) * 2 + 1.
*  Note:
*  Caller is responsable for deleting the kernel.
=============================================================
*/
vector<double> Msrcr::CreateKernel(double sigma)
{
	int i, x, filter_size;
	vector<double> filter;
	double sum;

	// set sigma's upline
	// Ϊsigma�趨����
	if (sigma > 300) sigma = 300;

	// get needed filter size (enforce oddness)
	// ��ȡ��Ҫ���˲��ߴ磬��ǿ��Ϊ������
	filter_size = (int)floor(sigma * 6) / 2;
	filter_size = filter_size * 2 + 1;

	// Calculate exponential
	// ����ָ��
	sum = 0;
	for (i = 0; i < filter_size; i++)
	{
		double tmpValue;
		x = i - (filter_size / 2);
		tmpValue = exp(-(x*x) / (2 * sigma*sigma));
		filter.push_back(tmpValue);

		sum += tmpValue;
	}

	// Normalize
	// ��һ������
	for (i = 0, x; i < filter_size; i++)
		filter[i] /= sum;

	return filter;
}

/*===========================================================
* ����: CreateFastKernel
* ˵��������һ�����Ƹ�����������ͣ�����8bits���Ŀ��ٸ�˹�ˣ�
* ������
*   double sigma: ��˹�˱�׼ƫ��
* ����ֵ��
*   double*: ����Ϊ((6*sigma)/2) * 2 + 1��int����
* ע��
*   ��������Ҫɾ�����ںˣ�
* --------------------------------------------------------
* Summary:
* Creates a faster gaussian kernal using integers that
* approximate floating point (leftshifted by 8 bits)
*
* Arguments:
* double sigma - the standard deviation of the gaussian kernel.
*
* Returns:
* vector<int> - an vector of values of length ((6*sigma)/2) * 2 + 1.
*
* Note:
* Caller is responsable for deleting the kernel.
=============================================================
*/
vector<int> Msrcr::CreateFastKernel(double sigma)
{
	vector<double> fp_kernel;
	vector<int> kernel;
	int i, filter_size;

	// Reject unreasonable demands
	// ��������
	if (sigma > 300) sigma = 300;

	// get needed filter size (enforce oddness)
	// ��ȡ��Ҫ���˲��ߴ磬��ǿ��Ϊ������
	filter_size = (int)floor(sigma * 6) / 2;
	filter_size = filter_size * 2 + 1;

	// Create Kernel
	// �����ں�
	fp_kernel = CreateKernel(sigma);

	// Change kernel's data type from double to int
	// double�ں�תΪint��
	for (i = 0; i < filter_size; i++)
	{
		int tmpValue;
		tmpValue = double2int(fp_kernel[i]);
		kernel.push_back(tmpValue);
	}

	return kernel;
}

/*===========================================================
* ������FilterGaussian
* ˵����ͨ���ں˼����˹������ں���sigmaֵ�õ��������ں�����ֵ��ȣ�
* ������
*   img: ���˲���IplImage*����ͼ��
*   double sigma: ��˹�˱�׼ƫ��
* --------------------------------------------------------
* Summary:
* Performs a gaussian convolution for a value of sigma that is equal
* in both directions.
*
* Arguments:
* IplImage* img - the image to be filtered in place.
* double sigma - the standard deviation of the gaussian kernel to use.
=============================================================
*/
void Msrcr::FilterGaussian(IplImage* img, double sigma)
{
	int i, j, k, source, filter_size;
	vector<int> kernel;
	IplImage* temp;
	int v1, v2, v3;

	// Reject unreasonable demands
	// ��������
	if (sigma > 300) sigma = 300;

	// get needed filter size (enforce oddness)
	// ��ȡ��Ҫ���˲��ߴ磬��ǿ��Ϊ������
	filter_size = (int)floor(sigma * 6) / 2;
	filter_size = filter_size * 2 + 1;

	// Create Kernel
	// �����ں�
	kernel = CreateFastKernel(sigma);

	temp = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);

	// filter x axis
	// X���˲�
	for (j = 0; j < temp->height; j++)
	{
		for (i = 0; i < temp->width; i++)
		{
			// inner loop has been unrolled
			// �ڲ�ѭ���Ѿ�չ��
			v1 = v2 = v3 = 0;
			for (k = 0; k < filter_size; k++)
			{
				source = i + filter_size / 2 - k;

				if (source < 0) source *= -1;
				if (source > img->width - 1) source = 2 * (img->width - 1) - source;

				v1 += kernel[k] * (unsigned char)pc(img, source, j, 0);
				if (img->nChannels == 1) continue;
				v2 += kernel[k] * (unsigned char)pc(img, source, j, 1);
				v3 += kernel[k] * (unsigned char)pc(img, source, j, 2);
			}

			// set value and move on
			pc(temp, i, j, 0) = (char)int2smallint(v1);
			if (img->nChannels == 1) continue;
			pc(temp, i, j, 1) = (char)int2smallint(v2);
			pc(temp, i, j, 2) = (char)int2smallint(v3);

		}
	}

	// filter y axis
	// Y���˲�
	for (j = 0; j < img->height; j++)
	{
		for (i = 0; i < img->width; i++)
		{
			v1 = v2 = v3 = 0;
			for (k = 0; k < filter_size; k++)
			{
				source = j + filter_size / 2 - k;

				if (source < 0) source *= -1;
				if (source > temp->height - 1) source = 2 * (temp->height - 1) - source;

				v1 += kernel[k] * (unsigned char)pc(temp, i, source, 0);
				if (img->nChannels == 1) continue;
				v2 += kernel[k] * (unsigned char)pc(temp, i, source, 1);
				v3 += kernel[k] * (unsigned char)pc(temp, i, source, 2);
			}

			// set value and move on
			pc(img, i, j, 0) = (char)int2smallint(v1);
			if (img->nChannels == 1) continue;
			pc(img, i, j, 1) = (char)int2smallint(v2);
			pc(img, i, j, 2) = (char)int2smallint(v3);

		}
	}

	cvReleaseImage(&temp);
}

/*===========================================================
* ������FilterGaussian
* ˵����ͨ���ں˼����˹������ں���sigmaֵ�õ��������ں�����ֵ��ȣ�
* ������
*   Mat src: ����ͼ��
*   Mat &dst: ���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
* --------------------------------------------------------
* Summary:
* Performs a gaussian convolution for a value of sigma that is equal
* in both directions.
*
* Arguments:
* Mat src - Input Image.
* Mat &dst - Output Image.
* double sigma - the standard deviation of the gaussian kernel to use.
=============================================================
*/
void Msrcr::FilterGaussian(Mat src, Mat &dst, double sigma)
{
	IplImage tmp_ipl;
	tmp_ipl = IplImage(src);
	FilterGaussian(&tmp_ipl, sigma);
	dst = cvarrToMat(&tmp_ipl);
}

/*===========================================================
* ������FastFilter
* ˵�������������С��sigmaֵ��������ͨ��ʹ��ͼ���������ɷ����˲��������˹�����
* ������
*   IplImage *img: ���˲���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
* --------------------------------------------------------
* Summary:
* Performs gaussian convolution of any size sigma very fast by using
* both image pyramids and seperable filters.  Recursion is used.
*
* Arguments:
* img - an IplImage to be filtered in place.
* double sigma - the standard deviation of the gaussian kernel to use.
=============================================================
*/
void Msrcr::FastFilter(IplImage *img, double sigma)
{
	int filter_size;

	// Reject unreasonable demands
	// ��������
	if (sigma > 300) sigma = 300;

	// get needed filter size (enforce oddness)
	// ��ȡ��Ҫ���˲��ߴ磬��ǿ��Ϊ������
	filter_size = (int)floor(sigma * 6) / 2;
	filter_size = filter_size * 2 + 1;

	// If 3 sigma is less than a pixel, why bother (ie sigma < 2/3)
	// ���3 * sigmaС��һ�����أ���ֱ���˳�
	if (filter_size < 3) return;

	// Filter, or downsample and recurse
	// ����ʽ��(1) �˲�  (2) ��˹�⻬����  (3) �ݹ鴦���˲�����С
	if (filter_size < 10) {

#ifdef USE_EXACT_SIGMA
		FilterGaussian(img, sigma);
#else
		cvSmooth(img, img, CV_GAUSSIAN, filter_size, filter_size);
#endif

	}
	else
	{
		if (img->width < 2 || img->height < 2) return;
		IplImage* sub_img = cvCreateImage(cvSize(img->width / 2, img->height / 2), img->depth, img->nChannels);
		cvPyrDown(img, sub_img);
		FastFilter(sub_img, sigma / 2.0);
		cvResize(sub_img, img, CV_INTER_LINEAR);
		cvReleaseImage(&sub_img);
	}
}

/*===========================================================
* ������FastFilter
* ˵�������������С��sigmaֵ��������ͨ��ʹ��ͼ���������ɷ����˲��������˹�����
* ������
*   Mat src: ����ͼ��
*   Mat &dst: ���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
* --------------------------------------------------------
* Summary:
* Performs gaussian convolution of any size sigma very fast by using
* both image pyramids and seperable filters.  Recursion is used.
*
* Arguments:
* Mat src - Input Image.
* Mat &dst - Output Image.
* double sigma - the standard deviation of the gaussian kernel to use.
=============================================================
*/
void Msrcr::FastFilter(Mat src, Mat &dst, double sigma)
{
	IplImage tmp_ipl;
	tmp_ipl = IplImage(src);
	FastFilter(&tmp_ipl, sigma);
	dst = cvarrToMat(&tmp_ipl);
}

/*===========================================================
* ������Retinex
* ˵������ͨ��SSR����������Retinex��ԭ�㷨��ԭͼ��ͱ��˲���ͼ����Ҫ��ת����
*   �����򣬲��������㣻
* ������
*   IplImage *img: ���˲���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
* --------------------------------------------------------
* Summary:
* Basic retinex restoration. The image and a filtered image are converted
* to the log domain and subtracted.
*
* Arguments:
* img - an IplImage to be enhanced in place.
* sigma - the standard deviation of the gaussian kernal used to filter.
* gain - the factor by which to scale the image back into visable range.
* offset - an offset similar to the gain.
=============================================================
*/
void Msrcr::Retinex(IplImage *img, double sigma, int gain, int offset)
{
	IplImage *A, *fA, *fB, *fC;

	// Initialize temp images
	// ��ʼ������ͼ��
	fA = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fB = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fC = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);

	// Compute log image
	// �������ͼ��
	cvConvert(img, fA);
	cvLog(fA, fB);

	// Compute log of blured image
	// �����˲���ģ��ͼ��Ķ���ͼ��
	A = cvCloneImage(img);
	FastFilter(A, sigma);
	cvConvert(A, fA);
	cvLog(fA, fC);

	// Compute difference
	// ������ͼ��֮��
	cvSub(fB, fC, fA);

	// Restore
	// �ָ�ͼ��
	cvConvertScale(fA, img, gain, offset);

	// Release temp images
	// �ͷŻ���ͼ��
	cvReleaseImage(&A);
	cvReleaseImage(&fA);
	cvReleaseImage(&fB);
	cvReleaseImage(&fC);

}

/*===========================================================
* ������Retinex
* ˵������ͨ��SSR����������Retinex��ԭ�㷨��ԭͼ��ͱ��˲���ͼ����Ҫ��ת����
*   �����򣬲��������㣻
* ������
*   Mat src: ����ͼ��
*   Mat &dst: ���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
* --------------------------------------------------------
* Summary:
* Basic retinex restoration. The image and a filtered image are converted
* to the log domain and subtracted.
*
* Arguments:
* Mat src - Input Image.
* Mat &dst - Output Image.
* sigma - the standard deviation of the gaussian kernal used to filter.
* gain - the factor by which to scale the image back into visable range.
* offset - an offset similar to the gain.
=============================================================
*/
void Msrcr::Retinex(Mat src, Mat &dst, double sigma, int gain, int offset)
{
	IplImage tmp_ipl;
	tmp_ipl = IplImage(src);
	Retinex(&tmp_ipl, sigma, gain, offset);
	dst = cvarrToMat(&tmp_ipl);
}

/*===========================================================
* ������MultiScaleRetinex
* ˵������ͨ��MSR�㷨��ԭͼ���һϵ�б��˲���ͼ��ת���������򣬲����Ȩ�ص�ԭͼ���������㡣
* ͨ������£�����Ȩ�ط�Χѡ��͡��С��߱�׼ƫ�
*
* ������
*   IplImage *img: ���˲���ͼ��
*   vector<double> weights: ͨ��Ȩ��
*   vector<double> sigmas: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
* --------------------------------------------------------
* Summary:
* Multiscale retinex restoration.  The image and a set of filtered images are
* converted to the log domain and subtracted from the original with some set
* of weights. Typicaly called with three equaly weighted scales of fine,
* medium and wide standard deviations.
*
* Arguments:
* IplImage* img - an IplImage to be enhanced in place.
* vector<double> weights - Weights of channels
* vector<double> sigma - the standard deviation of the gaussian kernal used to filter.
* int gain - the factor by which to scale the image back into visable range.
* int offset - an offset similar to the gain.
=============================================================
*/
void Msrcr::MultiScaleRetinex(IplImage *img, vector<double> weights, vector<double> sigmas, int gain, int offset)
{
	int i;
	double weight;
	int scales = sigmas.size();
	IplImage *A, *fA, *fB, *fC;

	// Initialize temp images
	fA = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fB = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fC = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);


	// Compute log image
	cvConvert(img, fA);
	cvLog(fA, fB);

	// Normalize according to given weights
	for (i = 0, weight = 0; i < scales; i++)
		weight += weights[i];

	if (weight != 1.0) cvScale(fB, fB, weight);

	// Filter at each scale
	for (i = 0; i < scales; i++)
	{
		A = cvCloneImage(img);
		double tmp = sigmas[i];
		FastFilter(A, tmp);

		cvConvert(A, fA);
		cvLog(fA, fC);
		cvReleaseImage(&A);

		// Compute weighted difference
		cvScale(fC, fC, weights[i]);
		cvSub(fB, fC, fB);
	}

	// Restore
	cvConvertScale(fB, img, gain, offset);

	// Release temp images
	cvReleaseImage(&fA);
	cvReleaseImage(&fB);
	cvReleaseImage(&fC);
}

/*===========================================================
* ������MultiScaleRetinex
* ˵������ͨ��MSR�㷨��ԭͼ���һϵ�б��˲���ͼ��ת���������򣬲����Ȩ�ص�ԭͼ���������㡣
* ͨ������£�����Ȩ�ط�Χѡ��͡��С��߱�׼ƫ�
*
* ������
*   Mat src: ����ͼ��
*   Mat &dst: ���ͼ��
*   vector<double> weights: ͨ��Ȩ��
*   vector<double> sigmas: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
* --------------------------------------------------------
* Summary:
* Multiscale retinex restoration.  The image and a set of filtered images are
* converted to the log domain and subtracted from the original with some set
* of weights. Typicaly called with three equaly weighted scales of fine,
* medium and wide standard deviations.
*
* Arguments:
* Mat src - Input Image.
* Mat &dst - Output Image.
* vector<double> weights - Weights of channels
* vector<double> sigmas - the standard deviation of the gaussian kernal used to filter.
* int gain - the factor by which to scale the image back into visable range.
* int offset - an offset similar to the gain.
=============================================================
*/
void Msrcr::MultiScaleRetinex(Mat src, Mat &dst, vector<double> weights, vector<double> sigmas, int gain, int offset)
{
	IplImage tmp_ipl;
	tmp_ipl = IplImage(src);
	MultiScaleRetinex(&tmp_ipl, weights, sigmas, gain, offset);
	dst = cvarrToMat(&tmp_ipl);
}

/*===========================================================
* ������MultiScaleRetinexCR
* ˵����MSRCR�㷨��MSR�㷨������ɫ�޸���ԭͼ���һϵ�б��˲���ͼ��ת���������򣬲����Ȩ�ص�ԭͼ���������㡣
* ͨ������£�����Ȩ�ط�Χѡ��͡��С��߱�׼ƫ�֮����ɫ�޸�Ȩ��Ӧ����ÿ����ɫͨ���У�
*
* ������
*   IplImage *img: ���˲���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
*   double restoration_factor: ������ɫ�޸��ķ�����
*   double color_gain: ������ɫ�޸�����
* --------------------------------------------------------
* Summary:
* Multiscale retinex restoration with color restoration.  The image and a set of
* filtered images are converted to the log domain and subtracted from the
* original with some set of weights. Typicaly called with three equaly weighted
* scales of fine, medium and wide standard deviations. A color restoration weight
* is then applied to each color channel.
*
* Arguments:
* IplImage *img - an IplImage to be enhanced in place.
* double sigma - the standard deviation of the gaussian kernal used to filter.
* int gain - the factor by which to scale the image back into visable range.
* int offset - an offset similar to the gain.
* double restoration_factor - controls the non-linearaty of the color restoration.
* double color_gain - controls the color restoration gain.
=============================================================
*/
void Msrcr::MultiScaleRetinexCR(IplImage *img, vector<double> weights, vector<double> sigmas,
	int gain, int offset, double restoration_factor, double color_gain)
{
	int i;
	double weight;
	int scales = sigmas.size();
	IplImage *A, *B, *C, *fA, *fB, *fC, *fsA, *fsB, *fsC, *fsD, *fsE, *fsF;

	// Initialize temp images
	// ��ʼ������ͼ��
	fA = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fB = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fC = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, img->nChannels);
	fsA = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
	fsB = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
	fsC = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
	fsD = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
	fsE = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);
	fsF = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_32F, 1);

	// Compute log image
	// �������ͼ��
	cvConvert(img, fB);
	cvLog(fB, fA);

	// Normalize according to given weights
	// ����Ȩ�ع�һ��
	for (i = 0, weight = 0; i < scales; i++)
		weight += weights[i];

	if (weight != 1.0) cvScale(fA, fA, weight);

	// Filter at each scale
	// ���߶��Ͻ����˲�����
	for (i = 0; i < scales; i++) {
		A = cvCloneImage(img);
		FastFilter(A, sigmas[i]);

		cvConvert(A, fB);
		cvLog(fB, fC);
		cvReleaseImage(&A);

		// Compute weighted difference
		// ����Ȩ�غ���ͼ��֮��
		cvScale(fC, fC, weights[i]);
		cvSub(fA, fC, fA);
	}

	// Color restoration
	// ��ɫ�޸�
	if (img->nChannels > 1) {
		A = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
		B = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
		C = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

		// Divide image into channels, convert and store sum
		// ��ͼ��ָ�Ϊ����ͨ��������ת��Ϊ�����ͣ����洢ͨ������֮��
		cvSplit(img, A, B, C, NULL);
		cvConvert(A, fsA);
		cvConvert(B, fsB);
		cvConvert(C, fsC);

		cvReleaseImage(&A);
		cvReleaseImage(&B);
		cvReleaseImage(&C);

		// Sum components
		// ���
		cvAdd(fsA, fsB, fsD);
		cvAdd(fsD, fsC, fsD);

		// Normalize weights
		// ��Ȩ�ؾ����һ��
		cvDiv(fsA, fsD, fsA, restoration_factor);
		cvDiv(fsB, fsD, fsB, restoration_factor);
		cvDiv(fsC, fsD, fsC, restoration_factor);

		cvConvertScale(fsA, fsA, 1, 1);
		cvConvertScale(fsB, fsB, 1, 1);
		cvConvertScale(fsC, fsC, 1, 1);

		// Log weights
		// ��Ȩ�ؾ��������
		cvLog(fsA, fsA);
		cvLog(fsB, fsB);
		cvLog(fsC, fsC);

		// Divide retinex image, weight accordingly and recombine
		// ��Retinexͼ���з�Ϊ�������飬����Ȩ�غ���ɫ�����������
		cvSplit(fA, fsD, fsE, fsF, NULL);

		cvMul(fsD, fsA, fsD, color_gain);
		cvMul(fsE, fsB, fsE, color_gain);
		cvMul(fsF, fsC, fsF, color_gain);

		cvMerge(fsD, fsE, fsF, NULL, fA);
	}

	// Restore
	// �ָ�ͼ��
	cvConvertScale(fA, img, gain, offset);

	// Release temp images
	// �ͷŻ���ͼ��
	cvReleaseImage(&fA);
	cvReleaseImage(&fB);
	cvReleaseImage(&fC);
	cvReleaseImage(&fsA);
	cvReleaseImage(&fsB);
	cvReleaseImage(&fsC);
	cvReleaseImage(&fsD);
	cvReleaseImage(&fsE);
	cvReleaseImage(&fsF);
}

/*===========================================================
* ������MultiScaleRetinexCR
* ˵����MSRCR�㷨��MSR�㷨������ɫ�޸���ԭͼ���һϵ�б��˲���ͼ��ת���������򣬲����Ȩ�ص�ԭͼ���������㡣
* ͨ������£�����Ȩ�ط�Χѡ��͡��С��߱�׼ƫ�֮����ɫ�޸�Ȩ��Ӧ����ÿ����ɫͨ���У�
*
* ������
*   Mat src: ����ͼ��
*   Mat &dst: ���ͼ��
*   double sigma: ��˹�˱�׼ƫ��
*   int gain: ͼ������ֵ�ı䷶Χ������
*   int offset: ͼ������ֵ�ı䷶Χ��ƫ����
*   double restoration_factor: ������ɫ�޸��ķ�����
*   double color_gain: ������ɫ�޸�����
* --------------------------------------------------------
* Summary:
* Multiscale retinex restoration with color restoration.  The image and a set of
* filtered images are converted to the log domain and subtracted from the
* original with some set of weights. Typicaly called with three equaly weighted
* scales of fine, medium and wide standard deviations. A color restoration weight
* is then applied to each color channel.
*
* Arguments:
* Mat src - Input Image.
* Mat &dst - Output Image.
* double sigma - the standard deviation of the gaussian kernal used to filter.
* int gain - the factor by which to scale the image back into visable range.
* int offset - an offset similar to the gain.
* double restoration_factor - controls the non-linearaty of the color restoration.
* double color_gain - controls the color restoration gain.
=============================================================
*/
void Msrcr::MultiScaleRetinexCR(Mat src, Mat &dst, vector<double> weights, vector<double> sigmas,
	int gain, int offset, double restoration_factor, double color_gain)
{
	IplImage tmp_ipl;
	tmp_ipl = IplImage(src);
	MultiScaleRetinexCR(&tmp_ipl, weights, sigmas, gain, offset, restoration_factor, color_gain);
	dst = cvarrToMat(&tmp_ipl);
}
