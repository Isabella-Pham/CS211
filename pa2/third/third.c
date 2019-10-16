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
      if(matrix[i][j] != 0){
        double c = matrix[i][j];
        matrix = subtractRows(matrix, i, j, col+col, c);
      }
    }
  }
  return matrix;
}

void printMatrix(double** matrix, int row, int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      printf("%lf\t", matrix[i][j]);
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

  //printMatrix(aug,row,col+col);

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

double** getW(double** x, double ** y, int row, int col){
  double** xT=(double**)malloc((col+1)*sizeof(double*));
	for(int i = 0; i < col+1; i++){
		xT[i]=(double*)malloc(row*sizeof(double));
	}
  double** xTx=(double**)malloc(col*sizeof(double*));
	for(int i = 0; i < col; i++){
		xTx[i]=(double*)malloc(col*sizeof(double));
	}
  double** xTxInv = (double**)malloc(col*sizeof(double*));
	for(int i = 0; i < col; i++){
		xTx[i]=(double*)malloc(col*sizeof(double));
	}
  double** xTxInvxT = (double**)malloc(col*sizeof(double*));
  for(int i = 0; i < col; i++){
    xTx[i]=(double*)malloc(row*sizeof(double));
  }
  double** w=(double**)malloc((col)*sizeof(double*));
  for(int i = 0; i < col; i++){
    w[i] = (double*)malloc(1*sizeof(double));
  }
  xT = transpose(x, row, col+1);
  xTx = multiply(xT, x, col, row, row, col);
  xTxInv = Gauss(xTx,col,col);
  //printMatrix(xTxInv,col,col);
  xTxInvxT = multiply(xTxInv,xT, col, col, col, row);
  w = multiply(xTxInvxT, y, col, row, row, 1);
  return w;
}

double** predict(double** test, double** w, int tests, int row, int col){
  double** y=(double**)malloc(tests*sizeof(double*));
  for(int i = 0; i < tests; i++){
    y[i]=(double*)malloc(1*sizeof(double));
  }
  double price = w[0][0];
  for(int i = 0; i < tests; i++){
    for(int j = 0; j < col-1; j++){
      price = price+(test[i][j]*w[j+1][0]);
    }
    y[i][0] = price;
  }
  return y;
}

int main(int argc, char *argv[]) {
  FILE * f = fopen(argv[1], "r"); //train file
  if(f == NULL){
    printf("error: file not found");
    return 0;
  }
  int xcol;
  fscanf(f,"%d\n", &xcol);
  //xcol = xcol + 1;
  int xrow;
  fscanf(f,"%d\n", &xrow);
  //allocating space for grid
  double** x=(double**)malloc(xrow*sizeof(double*));
  for(int i = 0; i < xrow; i++){
      x[i] = (double*)malloc((xcol+1)*sizeof(double));
  }
  double** y = (double**)malloc(xrow*sizeof(double*));
  for(int i = 0; i < xrow; i++){
    y[i] = (double*)malloc(1*sizeof(double));
  }
  //populate grid
  for(int i = 0; i < xrow; i++){
    x[i][0] = 1;
  }
  double num;
  for(int i = 0; i < xrow; i++){
    for(int j = 1; j < xcol+1; j++){;
      fscanf(f,"%lf%*[,]", &num);
      x[i][j] = num;
    }
    fscanf(f,"%lf", &num);
    y[i][0] = num;
    fscanf(f,"\n");
  }
  //x has dimensions xrow*xcol
  //y has dimensions xrow*1
  //w has dimensions (xcol-1)*1
  double** w=(double**)malloc((xcol)*sizeof(double*));
  for(int i = 0; i < xcol; i++){
    w[i] = (double*)malloc(1*sizeof(double));
  }
  w = getW(x, y, xrow, xcol); //creating weights
  //printMatrix(w, xcol-1, 1);
  FILE * test = fopen(argv[2], "r"); //train file
  if(test == NULL){
    printf("error: file not found");
    return 0;
  }
  int tests;
  fscanf(test,"%d\n",&tests);
  double** testmat=(double**)malloc(tests*sizeof(double*));
  for(int i = 0; i < tests; i++){
    testmat[i]=(double*)malloc((xcol)*sizeof(double));
  }
  double** prices=(double**)malloc(tests*sizeof(double*));
  for(int i = 0; i < tests; i++){
    prices[i]=(double*)malloc(1*sizeof(double));
  }
  for(int i = 0; i < tests; i++){
    for(int j = 0; j < xcol; j++){
      fscanf(test,"%lf%*[,]",&num);
      testmat[i][j] = num;
    }
    fscanf(test,"\n");
  }
  prices = predict(testmat, w, tests, xrow, xcol);
  printMatrix(prices, tests, 1);
  //printMatrix(w,xcol,1);
  return 0;
}
