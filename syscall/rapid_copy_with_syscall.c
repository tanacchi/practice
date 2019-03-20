#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int in_fd = open("./tmp.txt", O_RDONLY);

  struct stat st;
  fstat(in_fd, &st);

  const size_t block_size = st.st_blksize;
  char buff[block_size];

  int out_fd = open("./tmp3.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
  while (read(in_fd, buff, sizeof(char)*block_size) != 0)
  {
    write(out_fd, buff, sizeof(char)*block_size);
  }

  close(in_fd);
  close(out_fd);
  
  return 0;
}
