#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node * next;
}node;
void print(node * head){
  while(head != NULL){
    printf("%d ", head->data);
    head = head->next;
  }
}
int main(int argc, char** argv){
  /*FILE * f = fopen(argv[1], "r");
  if(ftell(f) == 0){
    printf("%d", 0);
    return 0;
  }*/
  int total = 0; //total number of nodes
  //struct node head;
  char operation;
  int n;
  /*while(!feof(fp)){
    fscanf(f,"%c\t%d", &operation, &n);
    if(operation == "i" && total == 0){
      head = new(n, head);
      total++;
    }
    if(operation == "i"){
      head = insert(n, head);
      total++;
    }else{
      head = delete(n, head);
      total--;
    }
  }*/
  node * head = (node*)malloc(sizeof(node)); //allocating space to node in memory
  head->data = 1;
  head->next = NULL;
  node * ptr = (node*)malloc(sizeof(node));
  head->next = ptr;
  ptr->data = 2;
  ptr->next=NULL;
  printf("%d\n", total);
  print(head);
  //fclose(f);
  return 0;
}
/*struct node new(int n, struct node *head){
  struct node *new = malloc(sizeof(struct node));
  new->n=n;
  new->next=head;
  return *new;
}*/
/*node* insert(int data; node* head){

}
node* delete(int data; node* head){

}*/
