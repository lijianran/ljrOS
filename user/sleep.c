
// 2021.06.05
// lijianran
// 调用sleep system call实现，执行 sleep 10，表示程序等待10个时钟周期（时器芯片的两次中断之间的时间）。

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "must have one argument for sleep\n");
        exit(1);
    }
    int sleepNum = atoi(argv[1]);
    printf("(nothing happens for a little while)\n");
    sleep(sleepNum);
    exit(0);
}