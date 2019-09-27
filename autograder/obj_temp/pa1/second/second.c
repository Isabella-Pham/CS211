#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node * next;
}node;
node* new(int data, node* next){
  struct node* newNode=(node*)malloc(sizeof(node));
  newNode->data=data;
  newNode->next=next;
  return newNode;
}
void print(node * head){
  while(head != NULL){
    if(head->next != NULL){
      printf("%d\t", head->data);
    }else{
      printf("%d",head->data);
    }
    head = head->next;
  }
}
node* insert(int data, node* head){
  node * add = new(data,NULL);
  if(head == NULL) return add; //add is the new head
  if(data<head->data){
    add->next=head;
    return add; //add is the new head;
  }
  if(data == head->data) return head;
  node * prev = head;
  node * ptr = head->next;
  while(ptr != NULL){
    if(data == ptr->data) return head;
    if(data < ptr->data){
      prev->next=add;
      add->next=ptr;
      return head;
    }
    prev = ptr;
    ptr = ptr->next;
  }
  if(ptr == NULL){ //add is the greatest element
    prev->next=add;
  }
  if(prev == head){ //head is the only element;
    head->next = add;
  }
  return head;
}
node* delete(int data, node* head){
  if(head==NULL) return head;
  if(head->data == data){
    return head->next; //delete the head
  }
  node * prev = head;
  node * ptr = head->next;
  while(ptr != NULL){
    if(ptr->data == data){
      prev->next=ptr->next;
      break;
    }
    prev = ptr;
    ptr = ptr->next;
  }
  return head;
}
int total(node* head){
  int num = 0;
  while(head != NULL){
    num++;
    head = head->next;
  }
  return num;
}
int main(int argc, char** argv){
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  int numNodes = 0; //total number of nodes
  node * head = NULL; //allocating space to node in memory
  char operation;
  int data;
  while(fscanf(f,"%c %d\n", &operation, &data) != EOF){
    if(operation == 'i'){
      head = insert(data, head);
    }else{
      head = delete(data, head);
    }
  }
  fclose(f);
  if(head == NULL){
    printf("%d", 0);
  }else{
    numNodes = total(head);
    printf("%d\n", numNodes);
    print(head);
  }
  return 0;
}
