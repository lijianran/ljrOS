#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i;
  // 参数小于 2 个
  if (argc < 2)
  {
    fprintf(2, "Usage: rm files...\n");
    exit(1);
  }
  // 循环删除链接
  for (i = 1; i < argc; i++)
  {
    // unlink 减少链接
    if (unlink(argv[i]) < 0)
    {
      fprintf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit(0);
}
