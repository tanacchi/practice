#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum Hand {
  HAND_FALSE,
  ROCK,
  SCISSORS,
  PAPER
};

enum Judge {
  DRAW,
  LOSE,
  WIN
};

int set_hand(const char* src) {
  static  const char* check_list[][7] = {
    { "rock",     "Rock",     "ROCK",     "goo",   "1" , "Goo"   , NULL },
    { "scissors", "Scissors", "SCISSORS", "CHOKI", "2" , "Choki" , NULL },
    { "paper",    "Paper",    "PAPER",    "PAA",   "3" , "Paa"   , NULL },
  };
  for (int i = 0; i < 3; i++)
    for (int j = 0; check_list[i][j] != NULL; j++)
      if (!strcmp(src, check_list[i][j])) return i+1;
  return HAND_FALSE;
}

int main() {
  
  srand((unsigned int)time(NULL));

  puts("Welcome to jaken game !");

  int user_hand;
  char input_hand[10];
  
  user_hand = HAND_FALSE;
  while (user_hand == HAND_FALSE) {
    printf("Input your hand!!\n> ");
    scanf("%s", input_hand);
    /* if (!strcmp(input_hand, "rock")) user_hand = ROCK; */
    /* else if (!strcmp(input_hand, "scissors")) user_hand = SCISSORS; */
    /* else if (!strcmp(input_hand, "paper")) user_hand = PAPER; */
    user_hand = set_hand(input_hand);
  }

  int cpu_hand = (int)rand() % 3 + 1;

  int judge = (user_hand - cpu_hand + 3) % 3;

  switch (judge) {
  case DRAW:
    printf("user = %d : cpu = %d\n", user_hand, cpu_hand);
    puts("DRAW!!");
    break;
  case LOSE:
    printf("user = %d : cpu = %d\n", user_hand, cpu_hand);
    puts("YOU LOSE...");
    break;
  case WIN:
    printf("user = %d : cpu = %d\n", user_hand, cpu_hand);
    puts("YOU WIN !!");
  }
  
  return 0;
}
