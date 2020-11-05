#include <stdio.h>
#include <unistd.h>

int main(void)
{
  int pid;
  pid = fork();
  printf("%d\n", pid);
}
