#include <highgui.h>
#include <math.h>

# define MAX_RETINEX_SCALES    8     /* Retinex最多可采用的尺度的数目 */
# define MIN_GAUSSIAN_SCALE   16     /* 最小Gaussian尺度 */
# define MAX_GAUSSIAN_SCALE  250     /* 最大Gaussian尺度 */

typedef struct
{
  int     scale;         /* 最大Retinex尺度 */
  int     nscales;       /* 尺度个数        */
  int     scales_mode;   /* Retinex尺度计算模式，有3种：UNIFORM, LOW, HIGH */
  float   cvar;          /* 用于调整色彩动态范围的方差的倍乘系数           */
} RetinexParams;

/* 3种Retinex尺度计算模式，均匀，低和高，它们决定RetinexScales中的尺度数据 */
# define RETINEX_UNIFORM 0
# define RETINEX_LOW     1
# define RETINEX_HIGH    2

/* 多尺度Retinex中需要的各个Retinex尺度保存在下面数组中 */
static float RetinexScales[MAX_RETINEX_SCALES];

typedef struct
{
  int    N;
  float  sigma;//高斯参数
  double B;
  double b[4];
} gauss3_coefs;

/*
 * Private variables.
 */
static RetinexParams rvals =
{
  240,             /* Scale */
  3,               /* Scales */
  RETINEX_UNIFORM, /* Retinex processing mode */
  1.2f             /* A variant */
};

# define clip( val, minv, maxv )    (( val = (val < minv ? minv : val ) ) > maxv ? maxv : val )

/*
 * calculate scale values for desired distribution.计算期望分布的标度值
 */
void retinex_scales_distribution( float* scales, int nscales, int mode, int s)
{
  if ( nscales == 1 )
  { /* For one filter we choose the median scale */
      scales[0] =  (float)s / 2;
  }
  else if (nscales == 2)
  { /* For two filters we choose the median and maximum scale */
      scales[0] = (float) s / 2;
      scales[1] = (float) s;
  }
  else
  {
      float size_step = (float) s / (float) nscales;
      int   i;

      switch( mode )
      {
        case RETINEX_UNIFORM:
          for ( i = 0; i < nscales; ++i )
            scales[i] = 2.0f + (float)i * size_step;
          break;

        case RETINEX_LOW:
          size_step = (float)log(s - 2.0f) / (float) nscales;
          for ( i = 0; i < nscales; ++i )
            scales[i] = 2.0f + (float)pow (10, (i * size_step) / log (10.f));
          break;

        case RETINEX_HIGH:
          size_step = (float) log(s - 2.0) / (float) nscales;
          for ( i = 0; i < nscales; ++i )
            scales[i] = s - (float)pow (10, (i * size_step) / log (10.f));
          break;

        default:
          break;
      }
    }
}

/*
 * Calculate the average and variance in one go.计算平均值和方差
 */
void compute_mean_var( float *src, float *mean, float *var, int size, int bytes )
{
  float vsquared;
  int i, j;
  float *psrc;

  vsquared = 0.0f;
  *mean = 0.0f;
  for ( i = 0; i < size; i+= bytes )
  {
       psrc = src+i;
       for ( j = 0 ; j < 3 ; j++ )
       {
            *mean += psrc[j];
            vsquared += psrc[j] * psrc[j];
       }
  }

  *mean /= (float) size; /* mean */
  vsquared /= (float) size; /* mean (x^2) */
  *var = ( vsquared - (*mean * *mean) );
  *var = (float)sqrt(*var); /* var */
}

/*
 * Calculate the coefficients for the recursive filter algorithm
 * Fast Computation of gaussian blurring.
 计算高斯核
 */
void compute_coefs3( gauss3_coefs * c, float sigma )
{
  /*
   * Papers:  "Recursive Implementation of the gaussian filter.",
   *          Ian T. Young , Lucas J. Van Vliet, Signal Processing 44, Elsevier 1995.
   * formula: 11b       computation of q
   *          8c        computation of b0..b1
   *          10        alpha is normalization constant B
   */
  float q, q2, q3;

  q = 0;

  if ( sigma >= 2.5f )
  {
      q = 0.98711f * sigma - 0.96330f;
  }
  else if ( (sigma >= 0.5f) && (sigma < 2.5f) )
  {
      q = 3.97156f - 4.14554f * (float) sqrt ((double) 1 - 0.26891 * sigma);
  }
  else
  {
      q = 0.1147705018520355224609375f;
  }

  q2 = q * q;
  q3 = q * q2;
  c->b[0] = (1.57825f+(2.44413f*q)+(1.4281f *q2)+(0.422205f*q3));
  c->b[1] = (         (2.44413f*q)+(2.85619f*q2)+(1.26661f *q3));
  c->b[2] = (                     -((1.4281f*q2)+(1.26661f *q3)));
  c->b[3] = (                                    (0.422205f*q3));
  c->B = 1.0f-((c->b[1]+c->b[2]+c->b[3])/c->b[0]);
  c->sigma = sigma;
  c->N = 3;
}

void gausssmooth( float *in, float *out, int size, int rowstride, gauss3_coefs *c )
{
  /*
   * Papers:  "Recursive Implementation of the gaussian filter.",
   *          Ian T. Young , Lucas J. Van Vliet, Signal Processing 44, Elsevier 1995.
   * formula: 9a        forward filter
   *          9b        backward filter
   *          fig7      algorithm
   */
  int i,n, bufsize;
  float *w1,*w2;

  /* forward pass 纵向处理*/
  bufsize = size+3;
  size -= 1;
  w1 = (float *)malloc (bufsize * sizeof (float));
  w2 = (float *)malloc (bufsize * sizeof (float));
  w1[0] = in[0];
  w1[1] = in[0];
  w1[2] = in[0];
  for ( i = 0 , n=3; i <= size ; i++, n++)
  {
     w1[n] = (float)(c->B*in[i*rowstride] +
                   ((c->b[1]*w1[n-1] +
                     c->b[2]*w1[n-2] +
                     c->b[3]*w1[n-3] ) / c->b[0]));
  }

  /* backward pass 横线处理*/
  w2[size+1]= w1[size+3];
  w2[size+2]= w1[size+3];
  w2[size+3]= w1[size+3];
  for ( i = size, n = i; i >= 0; i--, n-- )
  {
     w2[n]= out[i * rowstride] = (float)(c->B*w1[n] +
                                       ((c->b[1]*w2[n+1] +
                                         c->b[2]*w2[n+2] +
                                         c->b[3]*w2[n+3] ) / c->b[0]));
  }

  free (w1);
  free (w2);
}

void MSRCR( unsigned char * src, int width, int height, int bytes )
{
  int           scale, row, col;
  int           i, j;
  int           size;
  int           pos;
  int           channel;
  unsigned char *psrc = NULL;            /* backup pointer for src buffer */
  float         *dst  = NULL;            /* float buffer for algorithm */
  float         *pdst = NULL;            /* backup pointer for float buffer */
  float         *in, *out;
  int           channelsize;            /* Float memory cache for one channel */
  float         weight;
  gauss3_coefs  coef;
  float         mean, var;
  float         mini, range, maxi;
  float         alpha;
  float         gain;
  float         offset;

  /* Allocate all the memory needed for algorithm*/
  size = width * height * bytes;
  dst = (float *)malloc (size * sizeof (float));
  if (dst == NULL)
  {
      printf( "Failed to allocate memory" );
      return;
  }
  memset( dst, 0, size * sizeof (float) );

  channelsize  = ( width * height );
  in  = (float *)malloc (channelsize * sizeof (float));
  if (in == NULL)
  {
      free (dst);
      printf( "Failed to allocate memory" );
      return; /* do some clever stuff */
  }

  out  = (float *)malloc (channelsize * sizeof (float));
  if (out == NULL)
  {
      free (in);
      free (dst);
      printf( "Failed to allocate memory" );
      return; /* do some clever stuff */
  }

  /*
    Calculate the scales of filtering according to the
    number of filter and their distribution.
   */
  retinex_scales_distribution( RetinexScales,
                               rvals.nscales, rvals.scales_mode, rvals.scale );

  /*
    Filtering according to the various scales.
    Summerize the results of the various filters according to a
    specific weight(here equivalent for all).
   */
  weight = 1.0f / (float) rvals.nscales;

  /*
    The recursive filtering algorithm needs different coefficients according
    to the selected scale (~ = standard deviation of Gaussian).
   */
  pos = 0;
  //处理图像多个通道
  for ( channel = 0; channel < 3; channel++ )
  {
	  //获取所有像素
      for ( i = 0, pos = channel; i < channelsize ; i++, pos += bytes )
      {
            /* 0-255 => 1-256 */
            in[i] = (float)(src[pos] + 1.0);
      }
      for ( scale = 0; scale < rvals.nscales; scale++ )
      {
          compute_coefs3( &coef, RetinexScales[scale] );
          /*
           *  Filtering (smoothing) Gaussian recursive.
           *
           *  Filter rows first
           */
          for ( row = 0; row < height; row++ )
          {
              pos =  row * width;
              gausssmooth( in + pos, out + pos, width, 1, &coef );
          }

          memcpy( in,  out, channelsize * sizeof(float) );
          memset( out, 0  , channelsize * sizeof(float) );

          /*
           *  Filtering (smoothing) Gaussian recursive.
           *
           *  Second columns
           */
          for ( col = 0; col < width; col++ )
          {
              pos = col;
              gausssmooth( in + pos, out + pos, height, width, &coef );
          }

          /*
             Summarize the filtered values.
             In fact one calculates a ratio between the original values and the filtered values.
           */
          for ( i = 0, pos = channel; i < channelsize; i++, pos += bytes )
          {
              dst[pos] += weight * (float)( log(src[pos] + 1.0f) - log(out[i]) );
          }
          int k = 0 ;
      }
  }
  free(in);
  free(out);

  /*
    Final calculation with original value and cumulated filter values.
    The parameters gain, alpha and offset are constants.
  */
  /* Ci(x,y)=log[a Ii(x,y)]-log[ Ei=1-s Ii(x,y)] */

  alpha  = 128.0f;
  gain   = 1.0f;
  offset = 0.0f;

  for ( i = 0; i < size; i += bytes )
  {
      float logl;

      psrc = src+i;
      pdst = dst+i;

      logl = (float)log( (float)psrc[0] + (float)psrc[1] + (float)psrc[2] + 3.0f );

      pdst[0] = gain * ((float)(log(alpha * (psrc[0]+1.0f)) - logl) * pdst[0]) + offset;
      pdst[1] = gain * ((float)(log(alpha * (psrc[1]+1.0f)) - logl) * pdst[1]) + offset;
      pdst[2] = gain * ((float)(log(alpha * (psrc[2]+1.0f)) - logl) * pdst[2]) + offset;
    }

  /*
    Adapt the dynamics of the colors according to the statistics of the first and second order.
    The use of the variance makes it possible to control the degree of saturation of the colors.
  */
  pdst = dst;

  compute_mean_var( pdst, &mean, &var, size, bytes );
  mini = mean - rvals.cvar*var;
  maxi = mean + rvals.cvar*var;
  range = maxi - mini;

/*
  printf( "variance: \t\t%7.4f\n", var * rvals.cvar );
  printf( "mean: \t\t%7.4f\n", mean );
  printf( "min: \t\t%7.4f\n", mini );
  printf( "max: \t\t%7.4f\n", maxi );
  printf( "range: \t\t%7.4f\n", range );
*/

  if ( !range ) range = 1.0;

  for ( i = 0; i < size; i+= bytes )
  {
      psrc = src + i;
      pdst = dst + i;

      for (j = 0 ; j < 3 ; j++)
      {
          float c = 255 * ( pdst[j] - mini ) / range;

          psrc[j] = (unsigned char)clip( c, 0, 255 );
      }
  }

  free (dst);
}

int main()
{  
    IplImage * dst = NULL;
    IplImage *orig=cvLoadImage("H:\\test5.jpg",1);
    cvNamedWindow("Original",CV_WINDOW_AUTOSIZE);
    cvShowImage("Original",orig); 
    unsigned char * sImage, * dImage;
    int x, y;
    int nWidth, nHeight, step;
    nWidth = orig->width;
    nHeight = orig->height;
    step = orig->widthStep/sizeof( unsigned char );
    dst = cvCreateImage( cvSize(nWidth,nHeight), IPL_DEPTH_8U, 3 ); // 创建目标图像
    sImage = new unsigned char[nHeight*nWidth*3]; // 创建2个图像buffer
    dImage = new unsigned char[nHeight*nWidth*3];
    
    if ( orig->nChannels == 3 )
    {
        for ( y = 0; y < nHeight; y++ )
            for ( x = 0; x < nWidth; x++ )
            {
                sImage[(y*nWidth+x)*orig->nChannels] = orig->imageData[y*step+x*orig->nChannels];
                sImage[(y*nWidth+x)*orig->nChannels+1] = orig->imageData[y*step+x*orig->nChannels+1];
                sImage[(y*nWidth+x)*orig->nChannels+2] = orig->imageData[y*step+x*orig->nChannels+2];
            }
    }
    memcpy( dImage, sImage, nWidth*nHeight*orig->nChannels );
    /* 彩色图像增强 */
    MSRCR( dImage, nWidth, nHeight, orig->nChannels );
   
    for ( y = 0; y < nHeight; y++ )
        for ( x = 0; x < nWidth; x++ )
        {
            dst->imageData[y*step+x*3] = dImage[(y*nWidth+x)*3];
            dst->imageData[y*step+x*3+1] = dImage[(y*nWidth+x)*3+1];
            dst->imageData[y*step+x*3+2] = dImage[(y*nWidth+x)*3+2];
        }
        
    cvNamedWindow( "Result Video", CV_WINDOW_AUTOSIZE );
    cvShowImage( "Result Video", dst );
	cvWaitKey(0);
    cvReleaseImage( &orig );
    cvReleaseImage( &dst );
	cvDestroyWindow("Original");
	cvDestroyWindow("Result Video");
    delete [] sImage; // 清除图像buffer
    delete [] dImage;
}
