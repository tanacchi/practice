#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define width 80

int kansuu(int);
void print(void);
int com_num(int, char*);
void multiple_ary(void);
void prime_number(void);
int judge_prime(int);
void jyanken(void);
int input_plr(char*);
void com_practice(void);
void dictionary(void);
void help_menu(void);
void pointer_calc(void);
void struct_practice(void);

void nothing(void);

int main(int argc, char* argv[]){

  void (*command)(void);
  
  if (argc < 2){
    printf("ERROR!\n"
           "(Please add option)\n");
    return -1;
  }
  int i, com;
  for (i = 1; i < argc; i++){

    if (!strcmp(argv[i], "-a")) command = nothing;
    if (!strcmp(argv[i], "-b")) command = nothing;
    if (!strcmp(argv[i], "-c")) command = print;
    if (!strcmp(argv[i], "-d")) command = multiple_ary;
    if (!strcmp(argv[i], "-e")) command = prime_number;
    if (!strcmp(argv[i], "-f")) command = jyanken;	  
    if (!strcmp(argv[i], "-g")) command = nothing;
    if (!strcmp(argv[i], "-h")) command = help_menu;
    if (!strcmp(argv[i], "-i")) command = dictionary;
    if (!strcmp(argv[i], "-j")) command = pointer_calc;
    if (!strcmp(argv[i], "-k")) command = nothing;
    if (!strcmp(argv[i], "-l")) command = nothing;
    
    (*command)();
    
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

  char* plate[3][6] = {		/* 4x6 pointer array*/
    {"Rock",    "r", "1", "gu-",   "ROCK", NULL},
    {"scissors","s", "2", "choki", "SCISSORS", NULL},
    {"paper",   "p", "3", "pa-",   "PAPER", NULL},
  };

  int i, j, k;
  for (i = 0; i < 3; i++){
    for (j = 0; plate[i][j] != NULL; j++)
      printf("%s", plate[i][j]);
    putchar('\n');
  }  
}

void prime_number(void){

  int MAX;
  int num;
  int ans;
  int count = 0;

  char* ask;
  
  printf("this com is prime number!!\n");

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
  
      scanf("%s", insert);

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


void com_practice(void){

  char* ch;
  char com[2] = {};

  int com_num;

  
  scanf("%s", ch);

  if (!(strncmp(ch, "-", 1 )))
    printf("this is com header.\n");
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
  char* list[width][2] = {
    {"-a", "all com"},
    {"-b", "kansuu"},
    {"-c", "print"},
    {"-d", "multiple_ary"},
    {"-e", "prime_number"},
    {"-f", "jyanken"},
    {"-g", "com_practice"},
    {"-h", "help_menu"},
    {"-i", "dictionary"},
    {"-j", "pointer_calc"},
    {"-k", "struct_practice"},
    NULL
  };

  int i, j;
  for (i = 0; list[i][0] != NULL; i++){
    for (j = 0; j < 2; j++){
      printf("%s", list[i][j]);
      putchar('\t');
    }
    putchar('\n');
  }
}

void pointer_calc(void){

  char* str = "nkasdvnae";
  
  /* [*(str + i) ] ????  */
  
  int i, j;
  for (i = 0; *(str+i) != '\0'; i++){
    printf("%s\n", str+i);
    if (*(str+i) == 'd') printf("a\n");
  }
  
  putchar('\n');

  while (*(str++) != '\0'){
    printf("%s\n", str);
    if (*str == 'd') printf("[yeah]\n");
  }
  
  char* src[4] = {
    "jsdncvnewivn",
    "wvoineivdevn",
    "wjedfvbliwvb",
    NULL
  };

  for (i = 0; src[i] != NULL; i++){
    while (*(src[i]++) != '\0'){
      printf("%s\n", src[i]);
      if (*src[i] == 'i') printf("[yeah]\n");
    }
  }

  for (i = 0; src[i] != NULL; i++){
    for (j = 0; src[i][j] != '\0'; j++){
      if (src[i][j] == 'i'){
        printf("[yeah]\n");
      }
    }
  }
}

void nothing(void){
  ;

}
