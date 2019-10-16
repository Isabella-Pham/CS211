#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double** multiply(double** matrix1, double** matrix2, int row1, int row2, int col1, int col2){
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

double** transpose(double** matrix, int row, int col){
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

double** divideRow(double** matrix, int rowNum, int col, double constant){
  for(int i = 0; i < col; i++){
    matrix[rowNum][i] = matrix[rowNum][i]/constant;
  }
  return matrix;
}

double** subtractRows(double** matrix, int row1, int row2, int col, double c){
  for(int i = 0; i < col; i++){
    matrix[row1][i] = matrix[row1][i] - c*matrix[row2][i];
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

double** forward(double ** matrix, int row, int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j <= row; j++){
      if(matrix[i][j] != 0 && j < i){
        double c = matrix[i][j]/matrix[j][j];
        matrix = subtractRows(matrix, i, j, col+col, c);
      }
      if(matrix[i][j] != 1 && i == j){ //diagonal
        matrix = divideRow(matrix, i, col+col, matrix[i][j]);
      }
    }
  }
  return matrix;
}

double** backward(double** matrix, int row, int col){
  for(int i = row-1; i >= 0; i--){
    for(int j = col-1; j > i; j--){
      double c = matrix[i][j];
      matrix = subtractRows(matrix, i, j, col+col, c);
    }
  }
  return matrix;
}

void printMatrix(double** matrix, int row, int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      printf("%f\t", matrix[i][j]);
    }
    printf("\n");
  }
}

double** Gauss(double** matrix, int row, int col){
  double** aug= (double**)malloc((row*sizeof(double*)));
  for(int i = 0; i < col; i++){
    aug[i] = (double*)malloc((col+col)*sizeof(double));
  }
  //populate left side of augmented matrix w/ original matrix
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      aug[i][j] = matrix[i][j];
    }
  }
  //populate right side of augmented matrix w/ identity
  for(int i = 0; i < row; i++){
    for(int j = col; j < (col+col); j++){
      if(j-col == i){ //diagonal
        aug[i][j] = 1;
      }else{
        aug[i][j] = 0;
      }
    }
  }
  //forward elimination to create REF upper triangular matrix
  aug = forward(aug, row, col);
  //backward elimination to get to RREF
  aug = backward(aug, row, col);

  double** inverse = (double**)malloc(row*sizeof(double*));
  for(int i = 0; i < col; i++){
    inverse[i] = (double*)malloc(col*sizeof(double));
  }
  //retrieve inverse from augmented matrix
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      inverse[i][j] = aug[i][j+col];
    }
  }
  return inverse;
}

double** createMatrix(FILE * f){
  int col;
  fscanf(f,"%d\n", &col);
  col = col + 1;
  int row;
  fscanf(f, "%d\n", &row);
  //allocating space for grid
  double** grid=(double**)malloc(row*sizeof(double*));
  for(int i = 0; i < col; i++){
    grid[i] = (double*)malloc(col*sizeof(double));
  }
  //populate grid
  double num;
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      fscanf(f,"%0.0lf ", &num);
      grid[i][j] = num;
      printf("%0.0lf\n", num);
    }
  }
  return grid;
}

int main(int argc, char *argv[]) {
  FILE * f = fopen("test.txt", "r");
  //matrix = createMatrix(f);
  double a[3][3] = {{1,2,4},{1,6,7},{1,3,2}};
  double** grid=(double**)malloc(3*sizeof(double*));
  for(int i = 0; i < 3; i++){
    grid[i] = (double*)malloc(3*sizeof(double));
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      grid[i][j] = a[i][j];
    }
  }
  /*grid = forward(grid, 3, 3);
  grid = backward(grid,3, 3);*/
  grid = Gauss(grid,3,3);
  printMatrix(grid,3,3);
  return 0;
}
