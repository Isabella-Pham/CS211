#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  int size = 0;
  fscanf(f,"%d",&size);
  int num = 0;
  int** matrix = (int**)malloc(size*sizeof(int*));
  for(int i =0; i < size; i++){
    matrix[i] = (int*)malloc(size*sizeof(int));
  }
  int* numbers = (int*)malloc(size*size*sizeof(int));
  for(int i = 0; i < size*size; i++){
    numbers[i] = 0;
  }
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      fscanf(f,"%d\t", &num);
      matrix[i][j] = num;
      int index = num-1;
      if((size*size-1)<index || numbers[index] == 1){
        printf("not-magic");
        return 0;
      }else(numbers[num-1] == 0){
        numbers[num-1] = 1;
      }
    }
  }
  int sum = 0;
  //check diagonal
  for(int i = 0; i < size; i++){
    sum += matrix[i][i];
  }
  //check columns
  for(int i = 0; i < size; i++){
    int colSum = 0;
    for(int j = 0; j < size; j++){
      colSum += matrix[j][i];
    }
    if(colSum != sum){
      printf("not-magic");
      return 0;
    }
  }
  //check rows
  for(int i = 0; i < size; i++){
    int rowSum = 0;
    for(int j = 0; j < size; j++){
      rowSum += matrix[i][j];
    }
    if(rowSum != sum){
      printf("not-magic");
      return 0;
    }
  }
  printf("magic");
  //freeing 2d array
  for(int i = 0; i < size; i++){
    free(matrix[i]);
  }
  free(matrix);
  free(numbers);
  return 0;
}
