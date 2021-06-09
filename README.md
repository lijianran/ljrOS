# ljrOS

lijianran's Operation System

## 开发环境

- [官网教程](https://pdos.csail.mit.edu/6.S081/2020/tools.html) 
- vscode remote-container
- docker ubuntu20.04
- gcc g++ 9.3
- GNU Make 4.2.1
- gdb 9.2

## 开发日志

- 2021.06.04

    复习操作系统，开始学习 MIT6.S081 课程，完成一个操作系统内核

- 2021.06.05

1. 添加了 sleep 的简易版实现

- 2021.06.06

1. 通过 pipe 实现 pingpong
2. 通过 pipe 实现 primes，递归求解素数
3. 添加 find 的简易版实现
4. 添加 xargs 管道命令的简易版实现 [xargs 教程](http://www.ruanyifeng.com/blog/2019/08/xargs-tutorial.html) 

- 2021.06.09

1. 添加了系统调用 trace 的接口实现
2. 添加了系统调用 sysinfo 的接口实现
3. 添加了 sysinfo 的用户程序，查询当前空闲内存大小以及正在使用的线程个数