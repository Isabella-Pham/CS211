#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char c){
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
    return 1; //char c is a vowel
  }
  return 0;
}
int getLength(char * str){
  int length = 0;
  while(str[length] != '\0'){
    length++;
  }
  return length;
}
void newString(const char * str){
  char * string = (char *) str;
  int length = getLength(string);
  char c = string[0];
  int canPrint = 0;
  if(isVowel(c) == 1){
    printf("%syay",string);
  }else{
    for(int i = 0; i < length; i++){
      c = string[i];
      if(isVowel(c) == 1 || canPrint == 1){
        printf("%c",c);
        string[i] = '\0';
        canPrint = 1;
      }
    }
    length = getLength(string);
    for(int i = 0; i < length; i++){
      c = string[i];
      printf("%c",c);
    }
    printf("ay");
  }
}
int main(int argc, char const *argv[]) {
  if(argv[1] == NULL){
    printf("");
    return 0;
  }
  const char * str;
  for(int i = 1; i < argc; i++){
    str = argv[i];
    newString(str);
    printf(" ");
  }
  return 0;
}