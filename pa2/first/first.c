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
      fscanf(f,"%c", &num);
      grid[i][j] = num;
    }
  return grid;
  }
}

bool canAssign(char** grid, int *row, int *col, char hex){
  //returns true if hex is safe to assign to the box
  //checking if used in row
  if(grid[*row][*col] != '-') return false;
  for(int i = 0; i < 16; i++){
    if(grid[*row][i] == hex) return false;
    if(grid[*row][i] == '-'){
      *row = -1;
      *col = -1;
      return false;
    }
  }
  //checking if used in column
  for(int i = 0; i < 16; i++){
    if(grid[i][*col] == hex) return false;
    if(grid[i][*col] == '-'){
      *row = -1;
      *col = -1;
      return false;
    }
  }
  //checking if used in box
  int boxRow = *row-*row%3;
  int boxCol = *col-*col%3;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grid[boxRow+i][boxCol+j] == hex) return false;
    }
    if(grid[boxRow+i][boxCol+i] == '-'){
      *row = -1;
      *col = -1;
      return false;
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

void findEmpty(char** grid, int *row, int *col){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-'){
        *row = i;
        *col = j;
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
  if(i == 14) return 'E';
  if(i == 15) return 'F';
}

char** solve(char** grid){
  int row = 0;
  int col = 0;
  while(!isFilled(grid)){
    findEmpty(grid, &row, &col);
    int i;
    for(i = 0; i < 16; i++){
      char hex = getHex(i);
      if(canAssign(grid, &row, &col, hex)){
        grid[row][col] = hex;
      }
      if(row == -1 && col == -1) break;
    }
    if(i == 16) return NULL; //no numbers worked
  }
  return grid;
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

int main(int argc, char *argv[]){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  char** grid = createGrid(f);
  if(grid == NULL){
    printf("error");
    return 0;
  }
  grid = solve(grid);
  if(grid == NULL){
    printf("no-solution");
  }else{
    printGrid(grid);
  }
  return 0;
}
