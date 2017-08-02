CC=gcc
OUTPUT=-o
FLAG=-c
ALL=main.o callback.o string_sort.o transpose.o 
OBJ=test

$(OBJ):$(ALL)
	$(CC) $^ $(OUTPUT) $@
%.o:%.c
	$(CC) $(FLAG) $< $(OUTPUT) $@

.PHONY:clean
clean:
	@rm -rf *.o test
	@echo "del ok!"

