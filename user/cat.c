#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

void cat(int fd)
{
  int n;
  // 读出 n 个字符
  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    // 写入 stdout 的字符个数若不等于 n 则错误
    if (write(1, buf, n) != n)
    {
      fprintf(2, "cat: write error\n");
      exit(1);
    }
  }
  // read 出错
  if (n < 0)
  {
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  int fd, i;
  // 参数小于等于 1，循环打印 stdin 的内容
  if (argc <= 1)
  {
    cat(0);
    exit(0);
  }
  // 有多个参数，循环打开
  for (i = 1; i < argc; i++)
  {
    // 打开文件失败，结束
    if ((fd = open(argv[i], 0)) < 0)
    {
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    // 打开成功，打印内容
    cat(fd);
    // 关闭文件
    close(fd);
  }
  exit(0);
}
