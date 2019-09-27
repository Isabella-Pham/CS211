#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node * next;
}node;
typedef struct hashtable{
  struct node* table[1000];
}hashtable;
node* newNode(int data, node* next){
  struct node* newNode=(node*)malloc(sizeof(node));
  newNode->data=data;
  newNode->next=next;
  return newNode;
}
hashtable* newHashTable(){
  struct hashtable* newTable=(hashtable*)malloc(sizeof(hashtable));
  int i = 0;
  while(i < 1000){
    (newTable->table)[i] = NULL;
    i++;
  }
  return newTable;
}
int hashFunction(int n){ //returns the index to insert the value
  int key = n%1000;
  if(key < 0) key *= -1;
  return key;
}
int contains(int n, node* head){
  while(head != NULL){
    if(head->data == n) return 1;
    head=head->next;
  }
  return 0; //number is not contained
}
void print(node* numbers[]){
  int i = 0;
  while(i < 20){
    struct node* head = numbers[i];
    printf("%d :", i);
    while(head != NULL){
      printf("%d ", head->data);
      head=head->next;
    }
    printf("\n");
    i++;
  }
}
void freeNodes(node * head){
  node * ptr = head;
  while(ptr != NULL){
    ptr = head;
    head = head->next;
    free(ptr);
  }
}
void freehtable(node * table[]){
  for(int i = 0; i < 1000; i++){
    free(table[i]);
  }
  free(table);
}
int main(int argc, char const *argv[]) {
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  hashtable * htable = newHashTable();

  int data;
  char operation;
  int key;
  while(fscanf(f,"%c\t%d\n", &operation, &data) != EOF){
    key = hashFunction(data);
    if(operation == 'i'){ //insert
        if(contains(data,(htable->table)[key]) == 0){
          node * tmp = newNode(data, (htable->table)[key]);
          (htable->table)[key] = tmp;
          printf("inserted\n");
        }else{
          printf("duplicate\n");
        }
    }else{ //search
      if(contains(data, (htable->table)[key]) == 1){
        printf("present\n");
      }else{
        printf("absent\n");
      }
    }
  }
  fclose(f);
  freehtable(htable->table);
  return 0;
}
