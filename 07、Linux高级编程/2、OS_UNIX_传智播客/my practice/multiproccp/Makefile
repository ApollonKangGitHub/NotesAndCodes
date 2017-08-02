CPPFLAGS= -I ./
CFLAGS= -g -Wall
LDFLAGS= 
CC=gcc

src = $(wildcard *.c)
obj = $(patsubst %.c,%.o,$(src))
target = mpcp

$(target):$(obj)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(CPPFLAGS) -o $@

.PHONY:clean
clean:
	-rm -f *.o
	-rm -f mpcp

