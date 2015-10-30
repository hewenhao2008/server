# @Author: gatbsy
# @Date: 2015-10-8
# @Mail: i-careforu@foxmail.com
# @Brief: 配置服务器的makefile。

# 工程相关属性
PROJECT_NAME = serv
PLATFORM = LINUX
ARCH = _X86_

# 环境初始化
# ifeq ($(PLATFORM), LINUX)
#    CC = gcc
# endif

# 编译工具链
CC = gcc
CP = g++
LD = ld
AR = ar -tr
CC_OPTION = -DDEBUG -D$(ARCH) -D$(PLATFORM) -Wall # --std=c99
LD_OPTION = -lc -pthread

# SHELL命令
RM = rm -rf
CP = cp -r
ECHO = echo
BASH = bash 

# 依赖的头文件与链接库
INCLUDE := -I../include -I./
LD_LIBRARY_PATH :=
LD_LIBRARY :=

# 目标文件列表
OBJS = $(patsubst %.c, %.o, $(wildcard *.c, ./*.c))

# 目标
$(PROJECT_NAME): $(OBJS)
	$(CC) $(LD_OPTION) $(LD_LIBRARY_PATH) $(LD_LIBRARY) -o $@ $(OBJS)

# 隐含规则
.c.o:
	$(CC) $(CC_OPTION) $(INCLUDE) -c $<

# 清除编译过程中的中间文件
clean:
	-@$(ECHO) "[clean up workspace]"
	-@$(RM) $(PROJECT_NAME) makefile~ *.o *.h~ *.c~ 

# 安装服务器
install:
	-@$(ECHO) "[installing]"

# 伪目标
.PHONY: all clean install
