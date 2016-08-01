#include <stdio.h>

int kansuu(int x);

void print(void);

int command_num(int i, char src[]);

int main(int argc, char* argv[]){

  int command_num = -1;
  
  if (argc < 2){
    printf(
	   "\nERROR!\n"
	   "(Please add option)\n");
    return -1;
  }
  int i, command;
  for (i = 1; i < argc; i++){
    command = command_num(i, argv);

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

int command_num(int i, char src[]){ 

    if      (!(strcmp(src[i], "-a"))) return 0;
    else if (!(strcmp(src[i], "-b"))) return 1;
    else if (!(strcmp(src[i], "-c"))) return 2;
    else if (!(strcmp(src[i], "-d"))) return 3;
    else if (!(strcmp(src[i], "-e"))) return 4;
    else if (!(strcmp(src[i], "-f"))) return 5;
    else if (!(strcmp(src[i], "-g"))) return 6;
    else if (!(strcmp(src[i], "-h"))) return 7;
    else if (!(strcmp(src[i], "-i"))) return 8;
    else if (!(strcmp(src[i], "-j"))) return 9;
    else if (!(strcmp(src[i], "-k"))) return 10;
    else                              return -1;

}
    
