CPPFLAGS= -I ../ -I ./
CFLAGS= -g -Wall
LDFLAGS= 
CC=gcc
#CC=arm-linux-gcc

src = $(wildcard *.c)
obj = $(patsubst %.c,%.o,$(src))
target = client

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

#彻底清除生生过程文件
.PHONY:clean
clean:
	-rm -f client
	-rm -f *.o
