CC := gcc
LD := gcc
ECHO := echo
RM := rm
MAKE := make
DEV_NULL := /dev/null

INCLUDE = -I ./include/
#INCLUDE += -I ./tools/

CFLAGS = $(INCLUDE) 
LDFLAGS = -lpthread

OBJS = ./tftpMain.o
OBJS += ./src/tftpSocket.o
OBJS += ./src/tftpServer.o
#OBJS += ./src/tftpClient.o
OBJS += ./src/tftpLog.o
OBJS += ./src/tftpShell.o
#OBJS += ./src/tftpPack.o
OBJS += ./src/tftpTask.o
OBJS += ./src/tftpSem.o

#OBJS += ./tools/tools.o

DEP_FILES := $(patsubst %.o,%.d,$(OBJS))
DEP_FILES := $(wildcard $(DEP_FILES))

TARDIR := ./out/TFTP.exe
TARGETP_ROJECT := TFTP.exe
COMPILE_LOG := ./logFile/compile.log

ifneq ($(DEP_FILES),)
include $(DEP_FILES)
endif

$(TARGETP_ROJECT):$(OBJS)
	@$(ECHO) "DEP_FILES = $(DEP_FILES)"  >> $(COMPILE_LOG) && \
	$(ECHO) "OBJS = $(OBJS)"  >> $(COMPILE_LOG) && \
	$(ECHO) " commpile project $(TARGETP_ROJECT) is running..." | tee -a $(COMPILE_LOG) && \
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARDIR) && \
	$(ECHO) "link all files to target file $(TARGETP_ROJECT) succeed!" | tee -a $(COMPILE_LOG) || \
	$(ECHO) "link all files to target file $(TARGETP_ROJECT) failure!" | tee -a $(COMPILE_LOG) 
	
%.o:%.c
	@$(ECHO) "$< compile running..." | tee -a $(COMPILE_LOG) && \
	$(CC) -c $< $(CFLAGS) -o $@ -MD -MF $(patsubst %.c,%.d,$<) && \
	$(ECHO) "$< compile succeed!" | tee -a $(COMPILE_LOG) || \
	$(ECHO) "$< compile failure!" | tee -a $(COMPILE_LOG) 
	
.PHONY:clean
clean:
	@$(RM) -f $(OBJS) && \
	$(RM) -f $(TARDIR) && \
	$(ECHO) "delete module files and target file succeed!" | tee -a $(COMPILE_LOG) 
	
.PHONY:cleanDepend
cleanDepend:
	@$(RM) -f $(patsubst %.o,%.d,$(OBJS)) && \
	$(ECHO) "delete depend files succeed!" | tee $(COMPILE_LOG) 

.PHONY:cleanAll
cleanAll:
	@$(MAKE) clean >> $(DEV_NULL) && \
	$(MAKE) cleanDepend  >> $(DEV_NULL) && \
	$(ECHO) "delete target files and denpend files success!" || \
	$(ECHO) "delete target files and denpend files failed!"