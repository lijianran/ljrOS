
// 2021.06.06
// lijianran
// xargs

#include "kernel/types.h"
#include "user/user.h"
// #define MAXARG       32    main 最多 32 个参数
#include "kernel/param.h"

// 参数最大长度
#define MAX_LEN 100

int main(int argc, char *argv[])
{
    // 命令
    char *command = argv[1];
    // 字符缓存
    char bf;
    // 参数
    char paramv[MAXARG][MAX_LEN];
    // 参数的指针数组
    char *m[MAXARG];

    while (1)
    {
        // 参数个数
        int count = argc - 1;
        // 置空
        memset(paramv, 0, MAXARG * MAX_LEN);
        // 复制
        for (int i = 1; i < argc; i++)
        {
            strcpy(paramv[i - 1], argv[i]);
        }
        // 读每个参数的指针
        int cursor = 0;
        // 空格标志符 0代表空格 1代表字符
        int flag = 0;
        // read 读取后返回读取的字节个数
        int read_result;
        // 从 stdin 读数据，一次一个字符
        while (((read_result = read(0, &bf, 1))) > 0 && bf != '\n')
        {
            // 空格
            if (bf == ' ' && flag == 1)
            {
                // 参数个数加一
                count++;
                // 重置
                cursor = 0;
                flag = 0;
            }
            else if (bf != ' ')
            {
                // 存入数组
                paramv[count][cursor++] = bf;
                // 字符
                flag = 1;
            }
        }

        // 没有读到数据，表明遇到了 EOF
        if (read_result <= 0)
        {
            // 结束循环
            break;
        }
        // 读到了回车 bf='\n'
        for (int i = 0; i < MAXARG - 1; i++)
        {
            m[i] = paramv[i];
        }
        // 末尾标志符
        m[MAXARG - 1] = 0;
        // fork 进程执行命令
        if (fork() == 0)
        {
            // exec 执行 command 命令，将参数指针数组 m 输入
            exec(command, m);
            // 子进程结束
            exit(0);
        }
        else
        {
            // 父进程等待
            wait((int *)0);
        }
    }
    // 父进程结束
    exit(0);
}
