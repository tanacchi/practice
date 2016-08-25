#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define width 80

int kansuu(int x);
void print(void);
int command_num(int i, char src[]);
void multiple_ary(void);
void prime_number(void);
int judge_prime(int x;);
void jyanken(void);
int input_plr(char *src);
void command_practice(void);
void dictionary(void);
void help_menu(void);

int main(int argc, char* argv[]){
  
  if (argc < 2){
    printf(
	   "ERROR!\n"
	   "(Please add option)\n");
    return -1;
  }
  int i, command;
  for (i = 1; i < argc; i++){

    if      (!(strcmp(argv[1], "-all"))){
      argc = 10;
      command = i - 1;
    }
    else if (!(strcmp(argv[i], "-a"))) command = 0;
    else if (!(strcmp(argv[i], "-b"))) command = 1;
    else if (!(strcmp(argv[i], "-c"))) command = 2;
    else if (!(strcmp(argv[i], "-d"))) command = 3;
    else if (!(strcmp(argv[i], "-e"))) command = 4;
    else if (!(strcmp(argv[i], "-f"))) command = 5;
    else if (!(strcmp(argv[i], "-g"))) command = 6;
    else if (!(strcmp(argv[i], "-h"))) command = 7;
    else if (!(strcmp(argv[i], "-i"))) command = 8;
    else if (!(strcmp(argv[i], "-j"))) command = 9;
    else if (!(strcmp(argv[i], "-k"))) command = 10;
    else command = -1;


    switch (command){
    case -1:
      printf("command not be found\n");
      return -1;
    case 0:			/* -a */
      printf("kansuu=%d\n", kansuu(10));
      break;
    case 1:			/* -b */
      print();
      break;
    case 2:			/* -c */
      multiple_ary();
      break;
    case 3:			/* -d */
      prime_number();
      break;
    case 4:			/* -e */
      jyanken();
      break;
    case 5:			/* -f */
      /* command_practice(); */
      break;
    case 6:
      dictionary();             /* -g */
     break;
    case 7:			/* -h */
      help_menu();
      break;
    case 8:			/* -i */
      break;
    case 9:			/* -j */
      break;
    case 10:			/* -k */
      break;
	
    default:
      printf("task not be made\n");
    }
  }
  return 0;
}

int kansuu(int x){
  int y;
  y = x * 6 + 20;

  return y;
}

void print(void){

  printf("thank you (^ ^)\n");
  
}
    
void multiple_ary(void){

char* plate[3][5] = {		/* 4x6 pointer array*/
    {"Rock",    "r", "1", "gu-",   "ROCK"},
    {"scissors","s", "2", "choki", "SCISSORS"},
    {"paper",   "p", "3", "pa-",   "PAPER"},
};

  int i, j, k;
  for (i = 0; i < 3; i++){
    for (j = 0; j < 5; j++){
      /* for (k = 0; k < 10; k++){ */
  	printf("%s"/* "%c" */, plate[i][j]);
      /* } */
      putchar('\t');
    }
    putchar('\n');
  }  
}

void prime_number(void){

  int MAX;
  int num;
  int ans;
  int count = 0;

  char* ask;
  
  printf("this command is prime number!!\n");

  /* while (1){ */			
    count = 0;
    printf("insert MAX\n");
    scanf("%d", &MAX);
    putchar('\n');
    
    for (num = 2; num <= MAX; num++){
      ans = judge_prime(num);
      if (ans){
	printf("%d   ", num);
	count++;
      }
    }
    printf("\n[x%d]\n\n", count);
  
    /* printf("continue? (y/n)\n"); */
    /* scanf("%s", &ask); */
    /* if (!(strcmp(ask, "n"))) break; */
  /* } */
  
}

int judge_prime(int x){
  int y;

  for (y = 2; y <= (x / 2); y++){
    if (!(x % y)) return 0;
  }
  return 1;
}

void jyanken(void){

  int round = 1, win = 0, drw = 0;
  int plr, cpu;

  double rate = 0;

  char insert[width];
  char replay[width];  
  
  while(1){
    
    do{
      if (!(drw)){
	printf("\nJYANKEN..."
	       "\tround[%d]  win[%d]\n", round, win);
      }
      else{
	printf("\nAIKODE...[x%d]\n", drw);
      }
  
      scanf("%s", &insert);

      plr = input_plr(insert);
      if (plr == 0) printf("\n[TRY_AGAIN!!]");
      
    }while(!plr);

    srand((unsigned)time(NULL));
    cpu = (int)(rand() / (RAND_MAX+1.0)*3.0);
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

      if(strcmp(replay, "n") == 0)
	break;
      round++;
    }
  }
  printf("\nSee you~~\n\n");

}

int input_plr(char *src){
  
  char* board[3][5] = {
    {"rock",     "r", "ROCK",     "gu-",   "1"},
    {"scissors", "s", "SCISSORS", "choki", "2"},
    {"paper",    "p", "PAPER",    "pa-",   "3"}
  };

  int i, j;
  for (i = 0; i < 3; i++){
    for (j = 0; j < 5; j++){
      if (!(strcmp(src, board[i][j]))) return i + 1;
    }
  }
  return 0;
}


void command_practice(void){

  char* ch;
  char com[2] = {};

  int com_num;

  
  scanf("%s", &ch);

  if (!(strncmp(ch, "-", 1 )))
    printf("this is command header.\n");
  else
    printf("WTF\n");

  com_num = strncmp(ch, "-a", 2);
  printf("%d", com_num);
  
  /* strncpy(com, ch + 1, 1 ); */

  /* com_num = com[0]; */

  
  /* printf("%c\n", com_num); */
  /* int i; */
  /* printf("%d\n", com_num); */

}

void dictionary(void){

  char* input[9] = {"banana","grape","pear","orange","apple","strawberry","grapefruit","watermelon", '\0'};

  char* output[8] = {};
  char* ss;
  
  int i, j, k;
  for (i = 0; input[i] != '\0'; i++)
    printf("%s\n", input[i]);
  putchar('\n');
  
  for (i = 1; input[i] != '\0'; i++)
    for (j = 0; j < i; j++)
      if (strcmp(input[i], input[j]) < 0){
  	ss = input[i];
  	input[i] = input[j];
  	input[j] = ss;
      }
    
  for (i = 0; input[i] != '\0'; i++)
    printf("%s\n", input[i]);
  putchar('\n');
  
}

void help_menu(){
  char* list[9][2] = {
    {"-all", "perform all command"},
    {"-a", "kansuu"},
    {"-b", "print"},
    {"-c", "multiple_ary"},
    {"-d", "prime_number"},
    {"-e", "jyanken"},
    {"-f", "command_practice"},
    {"-g", "dictionary"},
    {"-h", "help_menu"}
  };

  int i, j;
  for (i = 0; i < 9; i++){
    for (j = 0; j < 2; j++){
      printf("%s", list[i][j]);
      putchar('\t');
    }
    putchar('\n');
  }
}

