#库以及路径
CPPFLAGS= -I ./ -I ../
#gcc的参数-g、-Wall等
CFLAGS=

LDFLAGS= 
#编译器类型
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
