#include <stdio.h>

int kansuu(int x);

void print(void);

int main(int argc, char* argv[]){

  int command_num = -1;
  
  if (argc < 2){
    printf(
	   "\nERROR!\n"
	   "(Please add option)\n");
    return -1;
  }
  int i;
  for (i = 1; i < argc; i++){
  
    if      (!(strcmp(argv[i], "-a"))) command_num = 0;
    else if (!(strcmp(argv[i], "-b"))) command_num = 1;
    else if (!(strcmp(argv[i], "-c"))) command_num = 2;
    else if (!(strcmp(argv[i], "-d"))) command_num = 3;
    else if (!(strcmp(argv[i], "-e"))) command_num = 4;
    else if (!(strcmp(argv[i], "-f"))) command_num = 5;
    else if (!(strcmp(argv[i], "-g"))) command_num = 6;
    else if (!(strcmp(argv[i], "-h"))) command_num = 7;
    else if (!(strcmp(argv[i], "-i"))) command_num = 8;
    else if (!(strcmp(argv[i], "-j"))) command_num = 9;
    else if (!(strcmp(argv[i], "-k"))) command_num = 10;
    else {
      printf("command not be found\n");
      return -1;
    }

    switch (command_num){
    
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

