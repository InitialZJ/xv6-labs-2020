#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "Invalid argument!\n");
    exit(1);
  }

  int t = atoi(argv[1]);
  int ret = sleep(t);
  exit(ret);
}
