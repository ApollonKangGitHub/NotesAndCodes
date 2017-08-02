#阶段四
CPPFLAGS= -I ../ -I ./
CFLAGS=
LDFLAGS= 
CC=gcc
#CC=arm-linux-gcc

src = $(wildcard *.c)
obj = $(patsubst %.c,%.o,$(src))
target = server

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

#彻底清除生生过程文件
.PHONY:clean
clean:
	-rm -f server
	-rm -f *.o
