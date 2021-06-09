
// 2021.06.09
// lijianran
// 调用 sysinfo system call 实现，查询当前空闲内存的大小以及正在执行的线程个数

#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    if (argc != 1)
    {
        fprintf(2, "sysinfo system call need not param\n");
        exit(1);
    }

    struct sysinfo info;
    sysinfo(&info);
    printf("free memory: %dbyte/%dm/%dG, used process: %d\n", info.freemem, info.freemem / 1024, info.freemem / 1024 / 1024, info.nproc);

    exit(0);
}
