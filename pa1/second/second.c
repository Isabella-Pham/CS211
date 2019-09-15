#include <stdio.h>
#include <stdlib.h>

struct node;
void print(struct node *node);
int main(int argc, char** argv) {
  FILE * f = fopen(argv[1], "r");
  if(ftell(f) == 0){
    printf("%d", 0);
    return 0;
  }
  int total = 0; //total number of nodes
  node head;
  char operation;
  int n;
  while(feof(fp) != 0){
    fscanf(f,"%c\t%d", &operation, &n);
    if(operation == "i" && total == 0){
      head = new(n, head);
    }
  }
  printf("%d\n", total);
  print(head);
  fclose(f);
  return 0;
}
struct node{
  int n;
  struct node *next;
}
node* new(int n, node* head){
  struct node* new = malloc(sizeof(struct node));
  new->n=n;
  new->next=head;
  return new;
}
void print(struct node *node){
  while(node != null){
    printf("%d ", (node->n));
    node = node -> next;
  }

}
