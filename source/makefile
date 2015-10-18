# 配置服务器的makefile

# 编译工具链
CC = gcc
LD = ld
AR = ar
CC_OPTION = -DDEBUG -Wall
LD_OPTION = -lc

# 工程相关属性
PROJECT_NAME = serv
PLATFORM = LINUX
ARCH = _X86_

# SHELL命令
EXECSH = /bin/sh -c
RM = rm -rf
CP = cp -r
ECHO = echo

# 依赖的头文件与链接库
INCLUDE := -I../include -I./
LIBPATH := 

# 目标文件列表
OBJS = $(patsubst %.c, %.o, $(wildcard *.c, ./*.c))

# 目标
$(PROJECT_NAME): $(OBJS)
	$(CC) $(LD_OPTION) -o $@ $(OBJS)

# 隐含规则
.c.o:
	$(CC) $(CC_OPTION) $(INCLUDE) -c $<

# 清除编译过程中的中间文件
clean:
	-@$(ECHO) "[clean up workspace] ×××"
	-@$(RM) $(PROJECT_NAME) makefile~ *.o *.h~ *.c~ 

# 安装服务器
install:
	@$(ECHO) "[installing] ×××"
	# @if [ $(id -u) -eq 1000 ]; then exit 1; fi

# 伪目标
.PHONY: all clean install
