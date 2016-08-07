#include <stdio.h>
#include <string.h>

int kansuu(int x);

void print(void);

int command_num(int i, char src[]);

void multiple_ary(void);

int main(int argc, char* argv[]){
  
  if (argc < 2){
    printf(
	   "\nERROR!\n"
	   "(Please add option)\n");
    return -1;
  }
  int i, command;
  for (i = 1; i < argc; i++){

    if      (!(strcmp(argv[i], "-a"))) command = 0;
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
    case 0:
      printf("kansuu=%d\n", kansuu(10));
      break;
    case 1:
      print();
      break;
    case 2:
      multiple_ary();
      break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
	
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
  	printf("%s"/* "%c" */, plate);
      /* } */
      putchar('\t');
    }
    putchar('\n');
  }  
}
