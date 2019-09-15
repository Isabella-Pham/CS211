#include <stdio.h>
#include <stdlib.h>

typedef struct node;
struct node* new(int n, struct node head);
void print(struct node node);
int main(int argc, char** argv){
  /*FILE * f = fopen(argv[1], "r");
  if(ftell(f) == 0){
    printf("%d", 0);
    return 0;
  }*/
  int total = 2; //total number of nodes
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
  struct node head = new(1, head);
  head->next = new(2, head->next);
  printf("%d\n", total);
  print(head);
  //fclose(f);
  return 0;
}
typedef struct node{
  int n;
  struct node *next;
}
struct node new(int n, struct node head){
  struct node new = malloc(sizeof(struct node));
  new->n=n;
  new->next=head;
  return new;
}
/*node* insert(int data; node* head){

}
node* delete(int data; node* head){

}*/
void print(struct node node){
  while(node != null){
    printf("%d ", (node->n));
    node = node -> next;
  }

}
