FILENAME = OvertimeTable

${FILENAME}.exe:${FILENAME}.c
	@gcc -E ${FILENAME}.c -o ${FILENAME}.i
	@gcc -S OvertimeTable.i -o ${FILENAME}.s
	@gcc -c ${FILENAME}.s -o ${FILENAME}.o
	@gcc ${FILENAME}.o -o ${FILENAME}.exe
	@echo "Compiled successfully, Please implement the .exe file first and last see the ".result" file!"
	
.PHONY:clean
clean:
	rm -f *.o *.i *.s *.exe
