#include <stdio.h>
#include <stdlib.h>

int isRightTruncatablePrime(int n);
int isPrime(int n);
int main(int argc, char** argv) {
  FILE * f = fopen(argv[1], "r");
  int n = 0;
  int total = 0;
  fscanf(f, "%d", &total);
  int i = 0;
  while(i < total){
    fscanf(f, "%d", &n);
    if(isRightTruncatablePrime(n) == 0){
      printf("no\n");
    }else{
      printf("yes\n");
    }
    i++;
  }
  fclose(f);
  return 0;
}
int isRightTruncatablePrime(int n){
  while(n > 0){
    if(isPrime(n) == 0) return 0;
    n = n/10;
  }
  return 1;
}
int isPrime(int n){
  if(n <= 1 || n%2==0) return 0; //negative numbers, 0, 1, even numbers aren't isPrime
  int i = 3;
  while(i < n/2){
    if(n%i == 0) return 0;
    i+=2;
  }
  return 1;
}
