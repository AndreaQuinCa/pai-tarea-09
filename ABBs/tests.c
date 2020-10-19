#include "abb.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_put_element(void);
int inOrderPrintTree(ABBNode* root);
void showRBT(ABBNode *root);

int main(int num_args, char ** args){
  int all_tests_ok = 1;
  all_tests_ok &= test_put_element();
  assert(all_tests_ok);
  return 0;
}

int test_put_element(void){
  printf("*- Test Put Element -*\n");
  // Create RBT
  ABBNode *trial;
  trial = newABBNode(11,1);
  put(trial,2,50);
  inOrderPrintTree(trial);
  printf("\n");
  put(trial,14,3);
  inOrderPrintTree(trial);
    printf("\n");

  put(trial,1,100);
  inOrderPrintTree(trial);
    printf("\n");

  put(trial,7,97);
  inOrderPrintTree(trial);
    printf("\n");

  /*trial = newABBNode(11,2);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,10) != 2)   {puts("ERROR"); return 0;}

  put(trial,2,15);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,2) != 15)   {puts("ERROR"); return 0;}

  inOrderPrintTree(trial);
  printf("\n");*/

  puts("OK");
  return 1;
}

int inOrderPrintTree(ABBNode* root){
    if(root != NULL){
        inOrderPrintTree(root->left);
        printf(" [key= %d, data = %d, color = %d]  ", root->key, root->data, root->color);
        inOrderPrintTree(root->right);
    }
}

void showsubtree(ABBNode *root, int space) { 
  ABBNode *temp;
  // Base case 
  if (root == NULL) return; 
  // Separacion de 10
  space += 10; 
  // Imprime subarbol derecho
  showsubtree(root->right, space); 
  printf("\n"); 
  for (int i = 10; i < space; i++) printf(" "); 
  printf("%d(%i)\n", root->key,root->color); 
  // Imprime subarbol izquierdo
  showsubtree(root->left, space); 
} 
  
void showRBT(ABBNode *root) { 
   showsubtree(root, 0); 
   printf("* **************************** *\n");
} 
