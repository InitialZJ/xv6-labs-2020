#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  int pid = fork();

  if (pid == 0) {
    char text[2];
    close(p[1]);
    read(p[0], text, 1);
    close(p[0]);
    printf("%d: received ping\n", getpid());
  } else {
    write(p[1], "x", 1);
    close(p[1]);
    wait((int *) 0);
    char text[2];
    read(p[0], text, 1);
    close(p[0]);
    printf("%d: received pong\n", getpid());
  }
  exit(0);
}
