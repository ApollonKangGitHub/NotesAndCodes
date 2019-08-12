CC := gcc
LD := gcc

INCLUDE = -I ./include/

CFLAGS = $(INCLUDE) 
LDFLAGS = -lpthread

OBJS = ./tftpMain.o
#OBJS += ./src/tftpServer.o
#OBJS += ./src/tftpClient.o
OBJS += ./src/tftpLog.o
OBJS += ./src/tftpShell.o
#OBJS += ./src/tftpPack.o
OBJS += ./src/tftpTask.o
#OBJS += ./src/tftpSem.o

DEP_FILES := $(patsubst %.o,%.d,$(OBJS))
DEP_FILES := $(wildcard $(DEP_FILES))

TARDIR := ./out/TFTP.exe
TARGETP_ROJECT := TFTP.exe
COMPILE_LOG := ./logFile/compile.log

ifneq ($(DEP_FILES),)
include $(DEP_FILES)
endif

$(TARGETP_ROJECT):$(OBJS)
	@echo "DEP_FILES = $(DEP_FILES)" >> $(COMPILE_LOG) && \
	echo "OBJS = $(OBJS)"  >> $(COMPILE_LOG) && \
	echo " commpile project $(TARGETP_ROJECT) is running..."  >> $(COMPILE_LOG) && \
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARDIR) && \
	echo "link all files to target file $(TARGETP_ROJECT) succeed!"  >> $(COMPILE_LOG) || \
	echo "link all files to target file $(TARGETP_ROJECT) failure!"  >> $(COMPILE_LOG) 
	
%.o:%.c
	@echo "$< compile running..."  >> $(COMPILE_LOG) && \
	$(CC) -c $< $(CFLAGS) -o $@ -MD -MF $(patsubst %.c,%.d,$<) && \
	echo "$< compile succeed!"  >> $(COMPILE_LOG) || \
	echo "$< compile failure!"  >> $(COMPILE_LOG) 
	
.PHONY:clean
clean:
	@rm -f $(OBJS) && \
	rm -f $(TARDIR) && \
	echo "delete module files and target file succeed!" >> $(COMPILE_LOG) 
	
.PHONY:cleanDepend
cleanDepend:
	@rm -f $(patsubst %.o,%.d,$(OBJS)) && echo "delete depend files succeed!" >> $(COMPILE_LOG) 