CC=gcc
FLAG=-c
OUTPUT=-o
ALL=test.o main.o ab.o dd.o cc.o ff.o
OBJ=test

$(OBJ):$(ALL)
	$(CC) $^  $(OUTPUT) $@ 
%.o:%.c
	$(CC) $(FLAG) $< $(OUTPUT) $@ 
.PHONY:clean
clean:
	@rm -rf *.o test
	@echo "del ok"


#	$@  代表当前规则的目标文件
#	$<  代表当前规则的第一个依赖文件
#	$^  代表当前规则的所有依赖文件

#main.o:main.c
#	$(CC) $(FLAG) $< $(OUTPUT) $@ 

