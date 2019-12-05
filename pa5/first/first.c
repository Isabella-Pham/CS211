#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
  char * name;
  int value;
  struct node* next;
}node;
int not(int in){
  if(int == 0) return 1;
  return 0;
}
int and(int in1, int in2){
  return in1*in2;
}
int or(int in1, int in2){
  return in1+in2;
}
int nand(int in1, int in2){
  return not(in1*int2);
}
int nor(int in1, int in2){
  return not(in1+in2);
}
int xor(int in1, int in2){
  if((in1 == 0 && in2 == 1) || (in1 == 1 && in2 == 0)) return 1;
  return 0;
}
int xnor(int in1, int in2){
  return not(xor(in1, in2));
}
int main(int argc, char *argv[]){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){ //file not found
    printf("error: file not found");
    return 0;
  }
  while(fscanf()){

  }
  return 0;
}
