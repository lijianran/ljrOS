#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
// sysinfo
#include "sysinfo.h"

uint64 sys_exit(void) {
    int n;
    if (argint(0, &n) < 0)
        return -1;
    exit(n);
    return 0;  // not reached
}

uint64 sys_getpid(void) { return myproc()->pid; }

uint64 sys_fork(void) { return fork(); }

uint64 sys_wait(void) {
    uint64 p;
    if (argaddr(0, &p) < 0)
        return -1;
    return wait(p);
}

uint64 sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

uint64 sys_sleep(void) {
    int n;
    uint ticks0;
    // 获得系统调用的参数 Fetch the nth 32-bit system call argument.
    if (argint(0, &n) < 0)
        return -1;
    // 加锁
    acquire(&tickslock);
    // 保存 sleep 时的时间戳
    ticks0 = ticks;
    // 循环睡眠
    while (ticks - ticks0 < n) {
        // 当前时间戳 - sleep 时的时间戳 < n
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        // sleep
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

uint64 sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64 sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

// 2021.06.09
// trace system call
uint64 sys_trace(void) {
    int n;

    if (argint(0, &n) < 0)
        return -1;
    myproc()->syscallnum = n;
    return 0;
}

// 2021.06.09
// sysinfo system call
uint64 sys_sysinfo(void) {
    // sysinfo 结构体的地址，从用户空间传进来的
    uint64 sysinfo_addr;
    // sysinfo 结构体
    struct sysinfo si;
    // 获得用户空间传进来的 sysinfo 结构体的地址，存入 sysinfo_addr
    if (argaddr(0, &sysinfo_addr) < 0)
        return -1;
    // 获得当前的空闲内存大小
    si.freemem = freememsize();
    // 获得当前正在执行的进行个数
    si.nproc = nproc_active();
    // 将 sysinfo 结构体的数据 copyout 到用户空间，也就是将 si 的内容复制到
    // sysinfo_addr 中
    if (copyout(myproc()->pagetable, sysinfo_addr, (char *)&si, sizeof(si)) < 0)
        return -1;
    return 0;
}
