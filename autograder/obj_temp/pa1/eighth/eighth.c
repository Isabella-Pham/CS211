#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node* left;
  struct node* right;
}node;
node* insert(node*root, int data, int height){
  node* add = (node*)malloc(sizeof(node));
  add->data=data;
  add->left=NULL;
  add->right=NULL;
  if(root == NULL){
    printf("inserted %d\n",height);
    return add;
  }
  if(data < root->data){
      root->left = insert(root->left,data,height+1);
  }else if(data > root->data){
    root->right = insert(root->right,data,height+1);
  }else{
    printf("duplicate\n");
    return root;
  }
  return root;
}
void search(node*root, int data, int height){
  if(root == NULL){
    printf("absent\n");
    return;
  }
  if(root->data == data){
    printf("present %d\n", height);
    return;
  }
  if(data < root->data) return search(root->left,data,height+1);
  if(data > root->data) return search(root->right,data,height+1);
}
void freeNode(node * root){
  if(root == NULL) return;
  freeNode(root->left);
  freeNode(root->right);
  free(root);
}
int main(int argc, char const *argv[]) {
  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    printf("error");
    return 0;
  }
  node * root = (node*)malloc(sizeof(node)); //allocating space to node in memory
  root = NULL;
  char operation;
  int data;
  while(fscanf(f,"%c %d\n", &operation, &data) != EOF){
    //printf("%d\n",data);
    if(operation == 'i'){ //insert
      root = insert(root, data, 1);
    }else{ //search
      search(root,data,1);
    }
  }
  fclose(f);
  freeNode(root);
  return 0;
}
