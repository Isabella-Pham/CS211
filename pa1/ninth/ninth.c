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
    return add; //add is the new root
  }
  if(data < root->data){
    root->left = insert(root->left,data,height+1);
  }else if(data > root->data){
    root->right = insert(root->right,data,height+1);
  }else{
    printf("duplicate\n");
    return root;
  }
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
node* delete(node*root, int data, int deleteInorder){
  if(root == NULL){
    printf("fail\n"); //could not find node to delete
    return NULL;
  }
  if(data < root->data){
    root->left = delete(root->left,data,0);
  }else if(data > root->data){
    root->right = delete(root->right,data,0);
  }else{ //delete this node
    node* replace = (node*)malloc(sizeof(node));
    if(root->left == NULL){
      replace = root->right;
      //if(deleteInorder == 0) printf("success\n");
      return replace;
    }else if(root->right == NULL){
      replace = root->left;
      //if(deleteInorder == 0) printf("success\n");
      return replace;
    }else{
      node* ptr = root->right;
      while((ptr != NULL) && (ptr->left != NULL)){ //find minimum value in right subtree
        ptr = ptr->left;
      }
      root->data = ptr->data;
      //if(deleteInorder == 0) printf("success\n");
      root->right = delete(root->right,ptr->data,1); //delete ptr
    }
    if(deleteInorder == 0) printf("success\n");
  }
  return root;
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
    if(operation == 'i'){ //insert
      root = insert(root, data, 1);
    }else if(operation == 's'){ //search
      search(root,data,1);
    }else{ //delete
      root = delete(root,data,0);
    }
  }
  fclose(f);
  return 0;
}
