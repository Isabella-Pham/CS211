#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double** multiply(double** matrix1, double** matrix2){
  int row1=sizeof(matrix1)/sizeof(matrix1[0]);
  int col1=sizeof(matrix1[0]/sizeof(matrix1[0][0]));
  int row2=sizeof(matrix2)/sizeof(matrix2[0]);
  int col2=sizeof(matrix2[0]/sizeof(matrix2[0][0]));
  //create result matrix
  double** result=(double**)malloc(row1*sizeof(double*));
  for(int i = 0; i < row1; i++){
    result[i] = (double*)malloc(col2*sizeof(double));
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

double** transpose(double** matrix){
  int row=sizeof(matrix)/sizeof(matrix[0]);
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  //create result matrix
  double** result=(double**)malloc(col*sizeof(double*));
  for(int i = 0; i < col; i++){
    result[i] = (double*)malloc(row*sizeof(double));
  }
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

double** divideRow(double** matrix, int row, int constant){
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  for(int i = 0; i < col; i++){
    matrix[row][i] = matrix[row][i]/constant;
  }
  return matrix;
}

double** subtractRows(double** matrix, int row1, int row2){
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  for(int i = 0; i < col; i++){
    matrix[row1][i] = matrix[row1][i] - matrix[row2][i];
  }
  return matrix;
}

bool isIdentity(double** matrix){
  //takes in an augmented matrix and returns true if the left side is the identity
  int row=sizeof(matrix)/sizeof(matrix[0]);
  for(int i = 0; i < row; i++){
    for(int j = 0; j < row; j++){
      if((i == j && matrix[i][j] != 1) || matrix[i][j] != 0){
        return false;
      }
    }
  }
  return true;
}

int** Gauss(int** matrix){
  int row=sizeof(matrix)/sizeof(matrix[0]);
  int col=sizeof(matrix[0]/sizeof(matrix[0][0]));
  int** aug= (int**)malloc((row*sizeof(int*));
  for(int i = 0; i < col; i++){
    aug[i] = (int*)malloc((col+col)*sizeof(int));
  }
  //populate left side of augmented matrix w/ original matrix
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      aug[i][j] = matrix[i][j];
    }
  }
  //populate right side of augmented matrix w/ identity
  for(int i = 0; i < row; i++){
    for(int j = 0; j < (col+col); j++){
      if(j-col == i){ //diagonal
        aug[i][j] = 1;
      }else{
        aug[i][j] = 0;
      }
    }
  }

  //forward elimination
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(i == j && matrix[i][j] != 1){

      }else if(i != j && matrix[i][j] != 0){

      }
    }
  }

  //Gausian elimination
  while(!isIdentity(matrix)){

  }
  double** inverse = (double**)malloc(row*sizeof(double*));
  //retrieve inverse from augmented matrix
  for(int i = 0; i < row; i++){
    for(int j = col; j < col; j++){
      inverse[i][j] = result[i][j+col];
    }
  }
  return inverse;
}
int main(int argc, char *argv[]) {
  /* code */
  return 0;
}
