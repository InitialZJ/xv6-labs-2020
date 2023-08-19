#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void help(int listenfd) {
  int forked = 0;
  int cur_num = 0;
  int passed_num = 0;
  int p[2];

  for (;;) {
    int len = read(listenfd, &passed_num, 4);
    if (len == 0) {
      close(listenfd);
      if (forked) {
        close(p[1]);
        wait((int *) 0);
      }
      exit(0);
    }

    if (cur_num == 0) {
      cur_num = passed_num;
      printf("prime %d\n", cur_num);
    }

    if (passed_num % cur_num != 0) {
      if (!forked) {
        pipe(p);
        forked = 1;
        int pid = fork();
        if (pid == 0) {
          close(p[1]);
          close(listenfd);
          help(p[0]);
        } else {
          close(p[0]);
        }
      }

      write(p[1], &passed_num, 4);
    }
  }
}

int
main(int argc, char *argv[])
{
  int i;
  int p[2];
  pipe(p);
  for (i = 2; i <= 35; i++) {
    write(p[1], &i, 4);
  }
  close(p[1]);
  help(p[0]);
  close(p[0]);
  exit(0);
}