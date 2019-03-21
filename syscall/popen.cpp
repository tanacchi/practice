#include <stdio.h>
#include <string.h>

int main()
{
  char str[512],*ptr;
  FILE *fp;

  if((fp=popen("ls -1","r"))==NULL){
    fprintf(stderr,"error!!!\n");
    return 0;
  }
  while(1){
    fgets(str,512,fp);
    if(feof(fp)){
      break;
    }
    ptr=strchr(str,'\n');
    if(ptr!=NULL){
      *ptr='\0';
    }
    printf("%s\n",str);
  }
  pclose(fp);

  return 0;
}
