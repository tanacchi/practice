#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

int input_plr(char* src);

int main(void){

  int round = 1, win = 0, drw = 0;
  int plr, cpu;

  double rate = 0;

  char insert[MAX];
  char replay[MAX];  
  
  while(1){

    putchar('\f');
    
    do{
      if (!(drw)){
        printf("\nJYANKEN..."
               "\v round[%d]  win[%d]  lose[%d]\n", round, win, round - win - 1
               );
      }
      else{
        printf("\nAIKODE...[x%d]\n", drw);
      }
  
      /* printf("\t\t\t\t(rock    scissors   paper)\n"); */
      scanf("%s", insert);

      plr = input_plr(insert);
      if (plr == 0) printf("TRY_AGAIN!!");
      
    }while(!plr);

    srand((unsigned)time(NULL));
    cpu = (int)rand() % 3 + 1;
    cpu++;

    int judge = (plr - cpu + 3) % 3;

    if(judge == 0){
      printf("\n\n[DRAW!!]\n");
      drw++;
    }
    else{
      if(judge == 1){
        printf("\n\n[YOU LOSE!!]\n");
      }
      else{
        win++;
        printf("\n\n[YOU WIN!!]\n");
      }
      drw = 0;
      rate = ((double)win / (double)round) * 100;
      printf("rate[%f]\n\n", rate);
      
      printf("PLAY MORE??\n[y/n]\n");
      scanf("%s", replay);
      
      if(!strcmp(replay, "y") == 0)
        break;
      round++;
    }
  }
  printf("\nSee you~~\n\n");
  
  return 0;
}

int input_plr(char *src){
  
  char* board[3][6] = {
    {"rock",     "r", "ROCK",     "gu-",   "1", NULL},
    {"scissors", "s", "SCISSORS", "choki", "2", NULL},
    {"paper",    "p", "PAPER",    "pa-",   "3", NULL}
  };
  
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; board[i][j] != NULL; j++)
      if (!strcmp(src, board[i][j])) return i + 1;
    
  return 0;
}
