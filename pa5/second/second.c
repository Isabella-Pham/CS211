#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct node{
  char * name;
  int value;
  struct node* next;
}node;
int not(int in){
  if(in == 0) return 1;
  return 0;
}
int and(int in1, int in2){
  return in1*in2;
}
int or(int in1, int in2){
  return in1+in2;
}
int nand(int in1, int in2){
  return not(in1*in2);
}
int nor(int in1, int in2){
  return not(in1+in2);
}
int xor(int in1, int in2){
  if((in1 == 0 && in2 == 1) || (in1 == 1 && in2 == 0)) return 1;
  return 0;
}
int xnor(int in1, int in2){
  return not(xor(in1, in2));
}
int** createGreyCode(int numInputs, int numOutputs){
  int numRows = pow (2, numInputs);
  int numCols = numInputs + numOutputs;
  int **greyCode = (int **) malloc (numRows * sizeof (int *));
  for (int i = 0; i < numRows; i++){
      greyCode[i] = (int *) malloc (numCols * sizeof (int));
  }
  int numOne = numRows / 2;
  int numZero = numRows / 2;
  for (int i = 0; i < numInputs; i++){
    int temp0 = numZero;
    int temp1 = numOne;
    for (int j = 0; j < numRows; j++){
     if (temp0 == 0 && temp1 == 0){
      if(j + temp0/2 == numRows){
          temp0 = temp0/2;
      }else{
          temp0 = numZero*2;
      }
      temp1 = numOne;
      }
      if (temp0 > 0){
        temp0--;
        greyCode[j][i] = 0;
      }else{
        temp1--;
        greyCode[j][i] = 1;
      }
    }
    if (i > 0) numOne = numOne / 2;
    numZero = numZero / 2;
  }
  return greyCode;
}
int** calcOutput(int** greyCode, int numInputs, int numOutputs, node * inputs, node * outputs, FILE * f){
  FILE * start = f; //start is the start of the circuit
  int numRows = pow (2, numInputs);
  int numCols = numInputs + numOutputs;
  char line[256];
  for(int i = 0; i < numRows; i++){
    while(fgets(line, sizeof(line), f)){
      printf("%s", line);
    }
    f = start; //move pointer back to start of circuit description
  }
  return greyCode;
}
void printGreyCode(int** greyCode, int numInputs, int numOutputs){
  int numRows = pow(2, numInputs);
  int numCols = numInputs + numOutputs;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      printf("%d ", greyCode[i][j]);
    }
    printf("\n");
  }
}
int main(int argc, char *argv[]){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){ //file not found
    printf("error: file not found");
    return 0;
  }
  int numInput = 0;
  fscanf(f, "INPUTVAR %d", &numInput);
  node* inputs = (node*)malloc(sizeof(node));
  char* name;
  node* ptr = inputs;
  for(int i = 0; i < numInput; i++){
    node* add = (node*)malloc(sizeof(node));
    fscanf(f, " %s", &name);
    add->name = name;
    ptr->next = add;
    ptr = add;
  }
  int numOutput = 0;
  fscanf(f, "OUTPUT %d", &numOutput);
  node* outputs = (node*)malloc(sizeof(node));
  ptr = outputs;
  for(int i = 0; i < numOutput; i++){
    node* add = (node*)malloc(sizeof(node));
    fscanf(f, " %s", &name);
    add->name = name;
    ptr->next = add;
    ptr = add;
  }
  int** greyCode = createGreyCode(numInput, numOutput);
  greyCode = calcOutput(greyCode, numInput, numOutput, inputs, outputs, f);
  return 0;
}
