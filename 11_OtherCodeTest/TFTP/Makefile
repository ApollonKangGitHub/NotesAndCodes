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

DEP_FILES := $(patsubst %.o,%.d,$(OBJS))
DEP_FILES := $(wildcard $(DEP_FILES))

TARDIR := ./out/TFTP.exe
TARGETP_ROJECT := TFTP.exe

ifneq ($(DEP_FILES),)
include $(DEP_FILES)
endif

$(TARGETP_ROJECT):$(OBJS)
	@echo "DEP_FILES = $(DEP_FILES)" && \
	echo "OBJS = $(OBJS)" && \
	echo " commpile project $(TARGETP_ROJECT) is running..." && \
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARDIR) && \
	echo "link all files to target file $(TARGETP_ROJECT) succeed!" || \
	echo "link all files to target file $(TARGETP_ROJECT) failure!"
	
%.o:%.c
	@echo "$< compile running..." && \
	$(CC) -c $< $(CFLAGS) -o $@ -MD -MF $(patsubst %.c,%.d,$<) && \
	echo "$< compile succeed!" || \
	echo "$< compile failure!"
	
.PHONY:clean
clean:
	@rm -f $(OBJS) && \
	rm -f $(TARDIR) && \
	rm -f $(OBJS) && \
	echo "delete module files and target file succeed!"
	
.PHONY:cleanDepend
cleanDepend:
	@rm -f $(patsubst %.o,%.d,$(OBJS)) && echo "delete depend files succeed!"
