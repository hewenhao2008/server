# 基于linux epoll的通用高并发框架

## 项目说明
本项目为本人自己闲暇时间写的一个试验性程序，用于原型验证，为了以后开发类似程序，可以快速适配而开发，尚不可应用于生产环境。

工程目前只支持基于`epoll` io复用的`linux`内核，尚未支持基于`kqueue`的`linux`内核，日后将要慢慢增加`kqueue`和`select`内核。

`epoll`部分的实现代码在，[source/epoll.c](https://github.com/keepalive555/server/blob/master/source/epoll.c)文件里。

进入源码目录`cd src/`，使用`make clean`命令清理中间文件，然后`make`一下编译工程，生成elf格式的可执行文件serv。

serv 的参数可通过`serv -h`，命令查看，-c 指定配置文件路径，-d 指定后台运行。程序的入口文件在[source/serv.c](https://github.com/keepalive555/server/blob/master/source/serv.c)

以后考虑借鉴redis的实现，加入tmalloc与jemalloc两种内存管理库，并且加入通用的dict实现方式与通用的词法parser实现。


