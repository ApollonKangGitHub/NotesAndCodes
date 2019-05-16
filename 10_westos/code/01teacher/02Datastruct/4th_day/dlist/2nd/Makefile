CC=gcc
FLAG=-c
OUTPUT=-o
ALL= main.o test.o
OBJ=test

$(OBJ):$(ALL)
	$(CC) $^ $(OUTPUT) $@
%.o:%.c
	$(CC) $(FLAG) $< $(OUTPUT) $@

.PHONY:clean
clean:
	@rm -rf *.o test	
	@echo "del ok"
