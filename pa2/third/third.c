#include <stdio.h>
#include <stdlib.h>

int** multiply(int** matrix1, int** matrix2){
  int row1=sizeof(matrix1)/sizeof(matrix1[0]);
  int col1=sizeof(matrix1[0]/sizeof(matrix1[0][0]));
  int row2=sizeof(matrix2)/sizeof(matrix2[0]);
  int col2=sizeof(matrix2[0]/sizeof(matrix2[0][0]));
  //create result matrix
  int** result=(int**)malloc(row1*sizeof(int*));
  for(int i = 0; i < row1; i++){
    result[i] = (int*)malloc(col2*sizeof(int));
  }
  //populate result with 0s
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col2; j++){
      result[i][j] = 0;
    }
  }
  for(int i = 0; i < row1; i++){
    for(int j = 0; j < col2; j++){
      for(int k = 0; k < col1; k++){
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return result;
}

int** transpose(int** matrix){
  int row=sizeof(matrix)/sizeof(matrix[0]);
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  //create result matrix
  int** result=(int**)malloc(col*sizeof(int*));
  for(int i = 0; i < col; i++){
    result[i] = (int*)malloc(row*sizeof(int));
  }
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

int** Gauss(int** matrix){
  int row=sizeof(matrix)/sizeof(matrix[0]);
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  int** aug= (int**)malloc((col+col)*sizeof(int*));
  for(int i = 0; i < col; i++){
    aug[i] = (int*)malloc(row*sizeof(int));
  }
}
int main(int argc, char *argv[]) {
  /* code */
  return 0;
}
