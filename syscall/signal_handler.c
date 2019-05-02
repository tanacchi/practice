#include <signal.h>
#include <stdio.h>

void signal_handler(int signum)
{
  printf("Signal received : signum = %d\n", signum);
}

int main()
{
  while (1)
  {
  puts("1. Ignore Ctrl-c");
  puts("2. Use costom handler");
  puts("3. Use default handler");
  puts("4. Raise SEGV");
  printf("Input your choice\n> ");

  char choice_string[200];
  int choice;
  fgets(choice_string, 200, stdin);
  sscanf(choice_string, "%d", &choice);

  switch (choice)
  {
    case 1:
      signal(SIGINT, SIG_IGN);
      break;
    case 2:
      signal(SIGINT, signal_handler);
      break;
    case 3:
      signal(SIGINT, SIG_DFL);
      break;
    case 4:
      raise(SIGSEGV);
      break;
    default:
      puts("Invalid input.");
  }
  }
  return 0;
}
