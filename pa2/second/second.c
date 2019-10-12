#include <stdio.h>
#include <stdlib.h>

char** createGrid(char *fileName){
  FILE * f = fopen(fileName, "r");
  if(f==NULL){
    return NULL;
  }
  //allocating space for grid
  char** grid=(char**)malloc(16*sizeof(char*));
  for(int i = 0; i < 16; i++){
    grid[i] = (char*)malloc(16*sizeof(char));
  }
  //populate grid
  char num;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      fscanf(f,"%c", &num);
      grid[i][j] = num;
    }
  return grid;
}
bool canAssign(char** grid, int row, int col, char assign){
  //returns true if assign is safe to assign to the box
  //checking if used in row
  if(grid[row][col] != '-') return false;
  for(int i = 0; i < 16; i++){
    if(grid[row][i] == assign) return false;
  }
  //checking if used in column
  for(int i = 0; i < 16; i++){
    if(grid[i][col] == assign) return false;
  }
  //checking if used in box
  int boxRow = row-row%3;
  int boxCol = col-col%3;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grid[boxRow+i][boxCol+j] == num) return false;
    }
  }
  return true;
}
bool isFilled(char** grid){
  //returns true if the grid is filled
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-') return false;
    }
  }
  return true;
}
void findEmpty(char** grid, int &row, int &col){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-'){
        row = i;
        col = j;
        return;
      }
    }
  }
  return;
}
char getHex(int i){
  if(i < 10) return i+'0';
  if(i == 10) return 'A';
  if(i == 11) return 'B';
  if(i == 12) return 'C';
  if(i == 13) return 'D';
  if(i == 14) return 'E'
  if(i == 15) return 'F';
}
bool solve(char** &grid){
  int row;
  int col;
  for(int i = 0; i < 16; i++){
    char hex = getHex(i);
    if(!isFilled(grid)){
      findEmpty(grid, row, col);
      grid[row][col] = hex;
      if(solve(grid) == true) return true;
    }
    grid[row][col] = '-';
  }
  return false;
}
int main(int argc, char *argv[]) {
  int** grid = createGrid(argv[1]);
  if(grid == NULL){
    printf("error");
    return 0;
  }
  if(solve(grid)){
    //printGrid
  }else{
    printf("no-solution");
  }
  return 0;
}
