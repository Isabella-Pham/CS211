#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  //creating matrix1
  int row1 = 0;
  fscanf(f,"%d",&row1);
  int col1 = 0;
  fscanf(f,"%d",&col1);
  int num = 0;
  int matrix1[row1][col1];
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col1; j++){
      fscanf(f,"%d", &num);
      matrix1[i][j] = num;
    }
  }
  //creating matrix2
  int row2 = 0;
  fscanf(f,"%d", &row2);
  int col2 = 0;
  fscanf(f,"%d",&col2);
  if(col1 != row2){
    printf("bad-matrices");
    return 0;
  }
  int matrix2[row2][col2];
  for(int i = 0; i < row2; i++){
    for(int j = 0; j < col2; j++){
      fscanf(f,"%d", &num);
      matrix2[i][j] = num;
    }
  }
  int result[row1][col2];
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col2; j++){
      result[i][j] = 0;
    }
  }
  //multiple rows of matrix1 by columns of matrix2
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col2; j++){
      for(int k = 0; k < col1; k++){
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  //print out the resulting matrix
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col2; j++){
      if(j < col2-1){
        printf("%d\t",result[i][j]);
      }else{
        printf("%d",result[i][j]);
      }
    }
    if(i < row1-1) printf("\n"); //don't print new line for last row
  }
  return 0;
}
