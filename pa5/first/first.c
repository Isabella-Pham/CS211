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
  if(in1 == 1 && in2 == 1) return 1;
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
void printLL(node* head){
  node* ptr = head;
  while(ptr != NULL){
    printf("%s: %d, ", ptr->name, ptr->value);
    ptr=ptr->next;
  }
  printf("\n");
}
node* addLL(node* head, char* name){
  node* add = (node*)malloc(sizeof(node));
  char* copy = (char*)malloc((strlen(name)+1)*sizeof(char));
  strcpy(copy, name);
  add->name = copy;
  add->next = NULL;
  if(head == NULL) return add;
  node* ptr = head;
  while(ptr->next != NULL){
    if(strcmp(ptr->name, name) == 0 || strcmp(ptr->next->name, name) == 0) return head;
    ptr = ptr->next;
  }
  ptr->next = add;
  return head;
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
int getValue(int** greyCode, node* inputs, node* outputs, char* inputName, int row){
  if(strcmp(inputName, "1") == 0){
    return 1;
  }
  if(strcmp(inputName, "0") == 0){
    return 0;
  }
  node* ptr = inputs;
  int col = 0;
  while(ptr != NULL){
    if(strcmp(ptr->name, inputName) == 0){
      return greyCode[row][col];
    }
    col++;
    ptr = ptr->next;
  }
  ptr = outputs;
  while(ptr != NULL){
    if(strcmp(ptr->name, inputName) == 0){
      return ptr->value;
    }
    ptr = ptr -> next;
  }
  printf("%s\n", inputName);
  return -1; //input value not found
}
node * setValue(node * outputs, char * outName, int out){
  node * ptr = outputs;
  while(ptr != NULL){
    if(strcmp(ptr->name, outName) == 0){
      ptr->value = out;
      break;
    }
    ptr = ptr->next;
  }
  return outputs;
}
int getMultiIndex(int* selectorInput, int numSelectors){
  int** greycode = createGreyCode(numSelectors, 0);
  int numRows = pow(2, numSelectors);
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numSelectors; j++){
      if(selectorInput[j] != greycode[i][j]) break;
      if(j == numSelectors-1) return i;
    }
  }
  return -1; //not found
}
int** calcOutput(int** greyCode, int numInputs, int numOutputs, node* inputs, node* outputs, FILE * f){
  //FILE * start = f; //start is the start of the circuit
  int numRows = pow(2, numInputs);
  int numCols = numInputs + numOutputs;
  char line[420];
  fgets(line, sizeof(line), f);
  for(int i = 0; i < numRows; i++){
    node* ptr = inputs;
    for(int j = 0; j < numInputs; j++){ //populate values for inputs
      ptr->value = greyCode[i][j];
      ptr = ptr->next;
    }
    while(fgets(line, sizeof(line), f)){
      char * token;
      token = strtok(line, " ");
      char * action = token;
      if(strcmp(action, "NOT") == 0){
        char * inName = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in = getValue(greyCode, inputs, outputs, inName, i);
        int out = not(in);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "AND") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = and(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out); //something wrong with setting output for second AND
      }else if(strcmp(action, "OR") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = or(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "NAND") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = nand(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "NOR") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = nor(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "XOR") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = xor(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "XNOR") == 0){
        char * in1Name = strtok(NULL, " \n");
        char * in2Name = strtok(NULL, " \n");
        char * outName = strtok(NULL, " \n");
        int in1 = getValue(greyCode, inputs, outputs, in1Name, i);
        int in2 = getValue(greyCode, inputs, outputs, in2Name, i);
        int out = xnor(in1, in2);
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }else if(strcmp(action, "DECODER") == 0){
        int numDecInputs = atoi(strtok(NULL, " \n"));
        int** grey = createGreyCode(numDecInputs,0);
        int rows = pow(2, numDecInputs);
        int* target = (int*)malloc(numDecInputs*sizeof(int));
        for(int j = 0; j < numDecInputs; j++){
          char* inName = strtok(NULL, " \n");
          target[j] = getValue(greyCode, inputs, outputs, inName, i);
        }
        int out = 1;
        for(int j = 0; j < rows; j++){
          for(int k = 0; k < numDecInputs; k++){
            if(grey[j][k] != target[k]) out = 0;
          }
          char* outName = strtok(NULL, " \n");
          outputs = addLL(outputs, outName);
          outputs = setValue(outputs, outName, out);
          out = 1;
        }
      }else if(strcmp(action, "MULTIPLEXER") == 0){
        //determine what value the selectors produce e.g. if produce 00 then choose the first multiplexer input
        char * numMultiInput = strtok(NULL, " \n");
        int num = atoi(numMultiInput);
        int multi[num];
        //populating the possible multiplexer inputs in an array
        for(int j = 0; j < num; j++){
          char * val = strtok(NULL, " \n");
          int input = getValue(greyCode, inputs, outputs, val, i);
          multi[j] = input;
        }
        //determining which multiplexer input to use based on selector
        int numSelectors = log2(num);
        int* selectorInput = (int*)malloc(numSelectors*sizeof(int));
        for(int j = 0; j < numSelectors; j++){
          char * selector = strtok(NULL, " \n");
          int selectorVal = getValue(greyCode, inputs, outputs, selector, i);
          selectorInput[j] = selectorVal;
        }
        int index = getMultiIndex(selectorInput, numSelectors);
        char * outName = strtok(NULL, " \n");
        int out = multi[index];
        outputs = addLL(outputs, outName);
        outputs = setValue(outputs, outName, out);
      }
      /*while(token != NULL){

      }*/
    }
    ptr = outputs;
    for(int j = numInputs; j < numCols; j++){
      greyCode[i][j] = ptr->value;
      ptr = ptr->next;
    }
    rewind(f); //move pointer back to start of circuit description
    fgets(line, sizeof(line), f); //skip input line
    fgets(line, sizeof(line), f); //skip output line
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
void freeLL(node* head){
  node* ptr;
  while(head != NULL){
    ptr = head;
    head = head->next;
    free(ptr);
  }
}
void freeGreyCode(int** greyCode, int numInput){
  int numRows = pow(2, numInput);
  for(int i = 0; i < numRows; i++){
    free(greyCode[i]);
  }
  free(greyCode);
}
int main(int argc, char *argv[]){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){ //file not found
    printf("error: file not found");
    return 0;
  }
  int numInput;
  fscanf(f, "INPUTVAR %d", &numInput);
  node* inputs = (node*)malloc(sizeof(node));
  inputs = NULL;
  char* name = (char*)malloc(21*sizeof(char));
  for(int i = 0; i < numInput; i++){
    fscanf(f, " %s", name);
    inputs = addLL(inputs, name);
  }

  int numOutput;
  fscanf(f, "\nOUTPUTVAR %d", &numOutput);
  node* outputs; //= (node*)malloc(sizeof(node));
  outputs = NULL;
  for(int i = 0; i < numOutput; i++){
    fscanf(f, " %s", name);
    outputs = addLL(outputs, name);
  }
  int** greyCode = createGreyCode(numInput, numOutput);
  greyCode = calcOutput(greyCode, numInput, numOutput, inputs, outputs, f);
  printGreyCode(greyCode, numInput, numOutput);
  freeLL(inputs);
  freeLL(outputs);
  freeGreyCode(greyCode, numInput);
  fclose(f);
  return 0;
}
