#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>

#define	RGB(r,g,b)	((r & 0xffff)<<16 | (g & 0xff) << 8 | b & 0xff)

int fix_screen(signed long* addr)
{
	int i, j;
	for(i=0; i<900; i++){
		for(j=0; j<1600; j++)
			*(addr + i*1600 + j) = RGB(0xffff, 0, 0);
	}
}
/*
int fix_screen_circle(signed long* addr)
{
	int i, j;
	int pos = 200;
	int r = 50;
	for(i=0; i<900; i++){
		for(j=0; j<1600; j++)
			if(((i-pos)*(i-pos)+(j-pos)(j-pos)) == r*r)
				*(addr + i*1600 + j) = RGB(0xffff, 0, 0);
	}
}
*/
int main()
{
	struct fb_var_screeninfo vinfo;

	int fd = open("/dev/fb0", O_RDWR);
	if(fd == -1){
		perror("open err.");
		exit(EXIT_FAILURE);
	}
	ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	printf("vinfo.xres: %d\n", vinfo.xres);
	printf("vinfo.yres: %d\n", vinfo.yres);
	printf("vinfo.bits_per_pixel: %d\n", vinfo.bits_per_pixel);

	unsigned long* addr =  mmap(0, ((vinfo.xres*vinfo.yres*vinfo.bits_per_pixel) >> 3),
			PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == (void*)-1){
		perror("mmap err. \n");
		exit(EXIT_FAILURE);
	}

	fix_screen(addr);	
//	fix_screen_circle(addr);
	close(fd);

	return 0;
}




