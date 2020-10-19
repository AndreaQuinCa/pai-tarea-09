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
  // probando con getdata
  if(getData(trial,2) != -1){puts("ERROR"); return 0;}

  put(trial,2,50);
  // Probando con getdata
  if(getData(trial,2) != 50){puts("ERROR"); return 0;}

  put(trial,14,7);
  // Probando con tamaño
  if(size(trial) != 3){puts("ERROR"); return 0;}

  put(trial,1,200);
  if(size(trial) != 4){puts("ERROR"); return 0;}
  if(contains(trial,14) != 1){puts("ERROR"); return 0;}

  put(trial,7,4);
  if(size(trial) != 5){puts("ERROR"); return 0;}
  if(getData(trial,200) != -1){puts("ERROR"); return 0;}

  showRBT(trial,trial->root);
  printf("\n");

  puts("OK");
  return 1;
}

int test_delete_esteban_element(void){
  printf("*- Test Delete Element -*\n");
  // Create RBT
RBTree *trial;
trial = newRBTree();
put(trial,11,1);
put(trial,2,50);
put(trial,14,7);
put(trial,1,200);
put(trial,7,4);
showRBT(trial,trial->root);

deleteNode(trial,1);
deleteNode(trial,11);

showRBT(trial,trial->root);


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

void showsubtree(RBTree *tree, ABBNode *root, int space) { 
  ABBNode *temp;
  // Si apunta a nil, no imprimo
  if (root == tree->nil) return; 
  // Separacion de 10
  space += 8; 
  // Imprime subarbol derecho
  showsubtree(tree, root->right, space); 
  printf("\n"); 
  for (int i = 8; i < space; i++) printf(" "); 
  printf("%d(%i)\n", root->key,root->color); 
  // Imprime subarbol izquierdo
  showsubtree(tree, root->left, space); 
} 
  
void showRBT(RBTree *tree, ABBNode *root) { 
  printf("* --------- R B  T r e e --------- *");
   showsubtree(tree, root, 0); 
   printf("* ----------------------------- *\n");
} 