#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

#include <unistd.h>

int main(void)
{
  int fd = open("/x", O_RDWR | O_CREAT, 0777);

  printf("fd = %d, errno=%d: %s\n", fd, errno, strerror(errno));

  if (fd != -1)
  {
    close(fd);
  }
  return 0;
}
