#include <stdio.h>
#include <stdlib.h>

int getLength(char * str){
  int length = 0;
  while(str[length] != '\0'){
    length++;
  }
  return length;
}
int main(int argc, char const *argv[]) {
  if(argv[1] == NULL){
    printf("");
    return 0;
  }
  char * str;
  for(int i = 1; i < argc; i++){
    str = (char *)argv[i];
    int length = getLength(str);
    char end = str[length-1];
    printf("%c",end);
  }
  return 0;
}
