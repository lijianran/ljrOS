
// 2021.06.06
// lijianran
// pipe primes
/*
素数筛法：将一组数 feed 到一个进程里，先 print 出最小的一个数，这是一个素数，
然后用其他剩下的数依次尝试整除这个素数，如果可以整除，则将其 drop，不能整除则将其 feed 到下一个进程中，直到最后打印出所有的素数。

采用递归，每次先尝试从左 pipe 中读取一个数，如果读不到说明已经到达终点，exit
否则再创建一个右 pipe 并 fork 一个子进程，将筛选后的数 feed 进这个右 pipe
*/
#include "kernel/types.h"
#include "user/user.h"

static void child(int *pl);

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        child(p);
    }
    else
    {
        // 关闭读端 input
        close(p[0]);
        // 循环写入
        for (int i = 2; i < 36; ++i)
        {
            // 向写端 output 写入
            write(p[1], &i, sizeof(int));
        }
        // 关闭写端
        close(p[1]);
        // 等待子进程结束
        wait((int *)0);
    }
    // 注意最开始的父进程要等待所有子进程 exit 才能 exit
    exit(0);
}

void child(int *pl)
{
    int pr[2];
    int n;
    // 关闭 p-left 写端 output
    close(pl[1]);
    // 从 p-left 读端，读取数据
    int read_result = read(pl[0], &n, sizeof(int));
    // 如果读取结果为 0，表明 pipe 的写端已经全部关闭
    if (read_result == 0)
        exit(0);
    // 还有数据，新建 pipe p-right
    pipe(pr);

    if (fork() == 0)
    {
        // 递归
        child(pr);
    }
    else
    {
        // 关闭 p-right 读端 input
        close(pr[0]);
        // 输出一个素数
        printf("prime %d\n", n);

        int prime = n;
        // 从 p-left 读端，读入数据到 n
        while (read(pl[0], &n, sizeof(int)) != 0)
        {
            // 判断 n 是否能整除当前最小的素数 prime，不能整除，则写入 p-right
            if (n % prime != 0)
            {
                // 向 p-right 写端写入数据
                write(pr[1], &n, sizeof(int));
            }
        }
        // 关闭 p-right 写端 output
        close(pr[1]);
        // 等待子进程结束
        wait((int *)0);
        exit(0);
    }
}
