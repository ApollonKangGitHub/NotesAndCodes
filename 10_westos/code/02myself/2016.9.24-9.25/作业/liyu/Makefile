C=gcc
OUTPUT=-o
FLAG=-c
ALL=main.o callback.o grape.o max.o
OBJ=test

$(OBJ):$(ALL)
	$(CC) $^ $(OUTPUT) $@
%.o:%.c
	$(CC) $(FLAG) $< $(OUTPUT) $@

.PHONY:clean
clean:
	@rm -rf *.o test
	@echo "ok!"

