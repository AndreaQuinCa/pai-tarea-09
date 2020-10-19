#include "abb.h"
#include "tests.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_put_element(void){
  printf("*- Test Put Element -*\n");
  // Create RBT
  RBTree *trial;
  trial = newRBTree();
  put(trial,11,1);
  inOrderPrintTree(trial,trial->root);
  printf("\n");
  put(trial,2,50);
  inOrderPrintTree(trial,trial->root);
  printf("\n");
  put(trial,14,7);
  inOrderPrintTree(trial,trial->root);
  printf("\n");
  put(trial,3,200);
  put(trial,5,4);


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

int inOrderPrintTree(RBTree *tree, ABBNode* root){
    if(root !=tree->nil){
        inOrderPrintTree(tree, root->left);
        printf(" [key= %d, data = %d, color = %d]  ", root->key, root->data, root->color);
        inOrderPrintTree(tree, root->right);
    }
}