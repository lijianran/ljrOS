
// 2021.06.06
// lijianran
// find

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *target_file);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "ERROR: You need pass in only 2 arguments\n");
        exit(1);
    }
    char *target_path = argv[1];
    char *target_file = argv[2];
    find(target_path, target_file);
    
    exit(0);
}

void find(char *path, char *target_file)
{
    // 句柄
    int fd;
    // 句柄属性
    struct stat st;
    // 目录
    struct dirent de;
    // buffer
    char buf[512], *p;
    // 打开路径
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "ERROR: cannot open %s\n", path);
        return;
    }
    // 获取属性到 st
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "ERROR: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // 循环读取 fd 所在的目录
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        // 拷贝路径到 buf
        strcpy(buf, path);
        // 指针 p 指向 buf 末尾
        p = buf + strlen(buf);
        // 给路径加上 /
        *p++ = '/';
        // 没有 inode 索引
        if (de.inum == 0)
            continue;
        // 拼接路径
        memmove(p, de.name, DIRSIZ);
        // 添加末尾标志符
        p[DIRSIZ] = 0;
        // 读取路径属性到 st
        if (stat(buf, &st) < 0)
        {
            fprintf(2, "ERROR: cannot stat %s\n", buf);
        }
        // 区分文件和目录
        switch (st.type)
        {
        case T_FILE:
            // 判断文件名是否是要查询的项目
            if (strcmp(target_file, de.name) == 0)
            {
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            // 不是当前目录（.）和上一目录（..）
            if ((strcmp(de.name, ".") != 0) && (strcmp(de.name, "..") != 0))
            {
                // 递归查询
                find(buf, target_file);
            }
        }
    }
    close(fd);
    return;
}
