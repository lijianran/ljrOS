
// 2021.06.06
// lijianran
// pipe

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    int p1[2];
    int p2[2];
    int pid;
    char buff[1];
    // 父进程写，子进程读
    pipe(p1);
    // 子进程写，父进程读
    pipe(p2);
    // fork 进程
    pid = fork();
    // pid=0 代表新 fork 出来的子进程
    if (pid < 0)
        exit(1);
    if (pid == 0)
    {
        // 子进程
        // 关闭 p1 写端
        close(p1[1]);
        // 关闭 p2 读端
        close(p2[0]);
        // 从 p1 的读端，读取数据到 buff
        read(p1[0], buff, sizeof(buff));
        // 打印
        printf("%d: received ping\n", getpid());
        // 向 p2 的写端，写入一字节数据
        write(p2[1], " ", 1);
        // 关闭所有 pipe
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }
    else
    {
        // 父进程
        // 关闭 p1 读端
        close(p1[0]);
        // 关闭 p2 写端
        close(p2[1]);
        // 向 p1 的写端，写入一字节数据
        write(p1[1], " ", 1);
        // 从 p2 的读端，读取数据到 buff
        read(p2[0], buff, sizeof(buff));
        // 打印
        printf("%d: received pong\n", getpid());
        // 关闭所有 pipe
        close(p1[1]);
        close(p2[0]);
        exit(0);
    }
}
