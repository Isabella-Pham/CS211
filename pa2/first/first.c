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

int getDec(char c){
  if(c == 'A') return 10;
  if(c == 'B') return 11;
  if(c == 'C') return 12;
  if(c == 'D') return 13;
  if(c == 'E') return 14;
  if(c == 'F') return 15;
  return c-'0';
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

bool canFill(char** grid){
  //returns true if the grid is not filled
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(grid[i][j] == '-') return true;
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

char * getOptions(char** grid, int row, int col){
  //returns an array of possible values a square could be
  char * options = (char*)malloc(16*sizeof(char)); //= {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; //possible options to use to fill empty spot
  for(int i = 0; i < 16; i++){
    options[i] = getHex(i);
  }
  //removing values based on row
  for(int i = 0; i < 16; i++){
    if(grid[row][i] == '-') continue;
    int dec = getDec(grid[row][i]);
    options[dec] = 'Z';
  }
  //removing values based on column
  for(int i = 0; i < 16; i++){
    if(grid[i][col] == '-') continue;
    int dec = getDec(grid[i][col]);
    options[dec] = 'Z';
  }
  //removing values based on box
  int boxRow = row-row%4;
  int boxCol = col-col%4;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(grid[boxRow+i][boxCol+j] == '-') continue;
      int dec = getDec(grid[boxRow+i][boxCol+j]);
      options[dec] = 'Z';
    }
  }
  return options;
}

char getChar(char * options){
  bool one = true;
  char ret;
  for(int i = 0; i < 16; i++){
    if(options[i] != 'Z'){
      if(!one){ //there are multiple options
        ret = 'Z';
        break;
      }
      ret = options[i];
      one = false;
    }
  }
  return ret;
}

char** solve(char** grid){
  int num = numLeft(grid);
  while(canFill(grid)){
    int i,j;
    for(i = 0; i < 16; i++){
      char c;
      for(j = 0; j < 16; j++){
        if(grid[i][j] == '-'){
          char * options = getOptions(grid, i, j);
          c = getChar(options);
          if(c != 'Z'){
            grid[i][j] = c;
          }
        }
      }
    }
    if(num == numLeft(grid)){
      return NULL; //nothing was changed, grid cannot be solved
    }else{
      num = numLeft(grid);
    }
  }
  return grid;
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
  grid = solve(grid);
  if(grid == NULL || !isLegitimate(grid)){
    printf("no-solution");
  }else{
    printGrid(grid);
  }
  return 0;
}
