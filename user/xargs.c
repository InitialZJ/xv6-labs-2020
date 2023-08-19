#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fd, i;
  char *args[MAXARG];
  char buf[1024];
  int n, m;
  char *p, *q;

  for (i = 1; i < argc; i++) {
    args[i - 1] = argv[i];
  }
  args[i] = 0;
  i--;

  fd = 0;
  m = 0;
  while((n = read(fd, buf+m, sizeof(buf)-m-1)) > 0){
    m += n;
    buf[m] = '\0';
    p = buf;
    while((q = strchr(p, '\n')) != 0){
      *q = 0;
      args[i] = p;
      int pid = fork();
      if (pid == 0) {
        int ret = exec(args[0], args);
        exit(ret);
      } else if (pid > 0) {
        wait((int *) 0);
      }
      p = q+1;
    }
    if(m > 0){
      m -= p - buf;
      memmove(buf, p, m);
    }
  }

  exit(0);
}

