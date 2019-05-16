#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>

#define	 RGB888(r, g, b)     ((0xff & r) << 11 | (0xff & g) << 5 | (b & 0xff))

void fix_color(unsigned long* addr)
{
	int i , j;
	for(i=100; i<700; i++){
		for(j=100; j<105; j=j++)
			*(addr + i*1376 + j) = RGB888(0xff, 0, 0);
	}
	for(i=100; i<105; i++){
		for(j=100; j<1300; j++)
			*(addr + i*1376 + j) = RGB888(0xff, 0, 0);
	}	
	for(i=100; i<700; i++){
		for(j=1300; j<1305; j++)
			*(addr + i*1376 + j) = RGB888(0xff, 0, 0);
	}
	for(i=700; i<705; i++){
		for(j=100; j<1300; j++)
			*(addr + i*1376 + j) = RGB888(0xff, 0, 0);
	}
}
int main()
{
	struct fb_var_screeninfo  vinfo;

	int fd = open("/dev/fb0", O_RDWR);
	if(fd < 0){
		perror("open err. \n");
		exit(EXIT_FAILURE);
	}
	int ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if(ret < 0){
		perror("ioctl err. \n");
		exit(EXIT_FAILURE);
	}
//	printf("vinfo.xres: %d\n", vinfo.xres);
//	printf("vinfo.yres: %d\n", vinfo.yres);
//	printf("vinfo.bits_per_pixel: %d\n", vinfo.bits_per_pixel);

	unsigned long* addr = mmap(NULL, (vinfo.xres*vinfo.yres*vinfo.bits_per_pixel)>>3,
				  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);	

	fix_color(addr);

	return 0;
}





