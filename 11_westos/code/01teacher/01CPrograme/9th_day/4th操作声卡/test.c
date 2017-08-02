#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/soundcard.h>

// modprobe  snd-pcm-oss
//采样率 、  量化位数 

int main(int argc, char *argv[])
{
	int fd = open("/dev/dsp", O_RDWR, 0777);
	if(fd < 0){
		perror("open err.");
		exit(EXIT_FAILURE);
	}
	
	int bit = 16;
	ioctl(fd, SOUND_PCM_WRITE_BITS, &bit);
//	SOUND_PCM_WRITE_BITS：设置声卡的量化位数，8位 、16位、 32位；	
//	模拟数据装换为数字信号的数据位数。

	int rate = 88200;
	ioctl(fd, SOUND_PCM_WRITE_RATE, &rate);
//设置声卡的采样频率	8K  16K
//11025Hz、22050Hz、44100Hz、88200Hz、176400Hz
	int pfd = open("beyond.wav", O_RDWR); 
	if(pfd < 0){
		perror("open beyond err.");
		exit(EXIT_FAILURE);
	}

	int size = lseek(pfd, 0, SEEK_END);
	printf("size: %d\n", size);
	lseek(pfd, 0, SEEK_SET);
	
	char *buff = malloc(size + 1);
	if(buff == NULL){
		perror("malloc err.");
		exit(EXIT_FAILURE);
	}
	int re = read(pfd, buff, size);
	printf("re: %d\n", re);
	
	int ret = write(fd, buff, size);
	printf("ret: %d\n", ret);
	
	close(fd);
	close(pfd);

	return 0;
}
























