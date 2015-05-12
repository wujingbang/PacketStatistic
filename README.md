PacketStatistic
===============

A tool to statistic packets from network stack of linux
这是一个基于libpcap抓包的小程序，用于精确统计实验数据包

# libpcap库的交叉编译
 1. ./configure --host=<交叉编译器前缀> --prefix=<交叉编译器目录>/lib/gcc/...../4.x.x  此为安装路径
     * 例：./configure --host=arm-none-linux-gnueabi
 2. make
 3. make install
 3. 将生成的libpcap.a文件拷贝到 <交叉编译器目录>/lib/gcc/...../4.x.x/ 目录下
 
 
# 工具的编译(以arm平台为例）
 1. 修改packet_statistic.c 中的#define DEV “...” 为adhoc对应的接口名
 2. arm-none-linux-gnueabi-g++ -o ...  packet_statistic.c -lpcap -static
 
 
# 使用注意事项：
 1. 源程序拷贝到设备中直接运行，运行时不能够强行退出
 2. 程序运行前需要保证接口正常运行
 3. 程序会检测接口down事件，并以此为结束标识将数据输出到sd卡，这意味着如果运行还未结束时关闭接口会使记录缺失（做断路实验时需要注意）。

