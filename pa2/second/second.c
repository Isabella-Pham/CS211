#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char** createGrid(FILE * f){
  //allocating space for grid
  char** grid=(char**)malloc(16*sizeof(char*));
  for(int i = 0; i < 16; i++){
    grid[i] = (char*)malloc(16*sizeof(char));
  }
  //populate grid
  char num;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      fscanf(f,"%c\t", &num);
      grid[i][j] = num;
    }
  }
  return grid;
}

char getHex(int i){
  if(i == 10) return 'A';
  if(i == 11) return 'B';
  if(i == 12) return 'C';
  if(i == 13) return 'D';
  if(i == 14) return 'E';
  if(i == 15) return 'F';
  return i+'0';
}

void printGrid(char** grid){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      printf("%c", grid[i][j]);
      if(j < 15) printf("\t");
    }
    if(i < 15) printf("\n");
  }
}

bool canFill(char** grid, int* row, int* col){
  //returns true if the grid is not filled
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-'){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

int numLeft(char** grid){ //returns the number of spaces left to solve
  int num = 0;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-') num++;
    }
  }
  return num;
}

bool canAssign(char** grid, int row, int col, char c){
  //checking row
  for(int i = 0; i < 16; i++){
    if(grid[row][i] == c && i!=col) return false;
  }
  //checking column
  for(int i = 0; i < 16; i++){
    if(grid[i][col] == c && i!=row) return false;
  }
  //checking box
  int boxRow = row-row%4;
  int boxCol = col-col%4;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(grid[boxRow+i][boxCol+j] == c && i!=row && j!=col) return false;
    }
  }
  return true;
}

bool solve(char** grid){
  if(numLeft(grid) == 0) printGrid(grid);
  int row,col;
  if(!canFill(grid, &row, &col)) return true;
  for(int i = 0; i < 16; i++){
    char hex = getHex(i);
    if(canAssign(grid, row, col, hex)){
      grid[row][col] = hex;
    }
    if(solve(grid)) return true;
    grid[row][col] = '-';
  }
  return false;
}

bool isLegitimate(char** grid){
  //checks that the grid does not break hexadoku rules
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      //check row
      char curr = grid[i][j];
      for(int k = 0; k < 16; k++){
        if(curr == grid[i][k] && k != j) return false;
      }
      //check column
      for(int k = 0; k < 16; k++){
        if(curr == grid[k][j] && k != i) return false;
      }
      //check box
      int boxRow = i-i%4;
      int boxCol = j-j%4;
      for(int k = 0; k < 4; k++){
        for(int l = 0; l < 4; l++){
          if(curr == grid[boxRow+k][boxCol+l] && boxRow+k != i && boxCol+l != j) return false;
        }
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error: file not found");
    return 0;
  }
  char** grid = createGrid(f);
  if(grid == NULL){
    printf("error: file is not correctly formatted or is empty");
    return 0;
  }
  bool solved = solve(grid);
  if(!solved || !isLegitimate(grid)){
    printf("no-solution");
  }/*else{
    printGrid(grid);
  }*/
  return 0;
}
