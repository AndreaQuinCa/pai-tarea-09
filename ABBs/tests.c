#include "abb.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>





int test_put_element(void){
  printf("*- Test Put Element -*\n");
  // Create RBT
  ABBNode *trial;

  trial = newABBNode(10,2);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,10) != 2)   {puts("ERROR"); return 0;}

  put(trial,2,15);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,2) != 15)   {puts("ERROR"); return 0;}


  puts("OK");
  return 1;
}

int inOrderPrintTree(ABBNode* root){
    if(root != NULL){
        inOrderPrintTree(x->left);
        printf(" [key= %d, data = %d]  ", root->key, root->data);
        inOrderPrintTree(x->right);
    }
}

