#include <stdio.h>
#include <string.h>

enum  Mode {
  MODE_OP,
  MODE_INPUT,
  MODE_JUDGE,
  MODE_OUTPUT,
  MODE_ASK,
  MODE_ED
};

Mode task_op(int* i);
Mode task_input(int* max);
Mode task_judge(int i, int max);
int isPrime(int src);
Mode task_output(int i);
Mode task_ask();
Mode task_ed();

int main() {
  Mode mode = MODE_OP;
  int max;
  int i = 1;
  
  while (1) {
    switch (mode) {
    case MODE_OP:
      mode = task_op(&i);
      break;
    case MODE_INPUT:
      mode = task_input(&max);
      break;
    case MODE_JUDGE:
      mode = task_judge(++i ,max);
      break;
    case MODE_OUTPUT:
      mode = task_output(i);
      break;
    case MODE_ASK:
      mode = task_ask();
      break;
    case MODE_ED:
      mode = task_ed();
      return 0;
    }
  }
  
  return 0;
}

Mode task_op(int *i) {
  *i = 1;
  printf("\n------------------PRIME NUMBER FINDER --------------------------\n"
         "Input MAX number.\n"
         "I will show you prime numbers smaller than MAX.\n");
  return MODE_INPUT;
}

Mode task_input(int* max) {
  printf("> ");
  scanf("%d", max);
  putchar('\n');
  return MODE_JUDGE;
}

Mode task_judge(int i, int max) {
  if (i > max) return MODE_ASK;
  if (isPrime(i)) return MODE_OUTPUT;
  else return MODE_JUDGE;
}

int isPrime(int src) {
  for (int i = 2; i <= (src / 2); i++)
    if (!(src % i)) return 0;
  return 1;
}

Mode task_output(int i) {
  printf("%d\t\t", i);
  return MODE_JUDGE;
}

Mode task_ask() {
  char answer[8];
  printf("\nAGAIN??\t\t[yes/no]\n"
         "> ");
  scanf("%7s", answer);
  if (!strcmp(answer, "yes")) return MODE_OP;
  else if (!strcmp(answer, "no")) return MODE_ED;
  else return MODE_ASK;
}

Mode task_ed() {
  printf("See you~~\n");
  return MODE_ED;
}
