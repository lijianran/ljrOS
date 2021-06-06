#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i;
  // 多个参数
  for (i = 1; i < argc; i++)
  {
    // 向 stdout 打印参数内容
    write(1, argv[i], strlen(argv[i]));
    // 还有参数，输出一个空格来分割
    if (i + 1 < argc)
    {
      write(1, " ", 1);
    }
    else
    {
      // 没有参数了，输出回车
      write(1, "\n", 1);
    }
  }
  exit(0);
}
