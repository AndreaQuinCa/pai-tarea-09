#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "abb.h"

void inOrderPrintTree(RBTree *tree, ABBNode* root){
    if(root !=tree->nil){
        inOrderPrintTree(tree, root->left);
        printf(" [key= %d, data = %d, color = %d]  ", root->key, root->data, root->color);
        inOrderPrintTree(tree, root->right);
    }
}

void showsubtree(RBTree *tree, ABBNode *root, int space) {
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

int test_delete_element(void){
    printf("*- Test Delete Element -*\n");
    /*El test prueba los 4 casos de liberación según el color del hermano y
    de los sobrinos del nodo que se quiere liberar. Para encontrar un árbol
    de cada caso utlicé https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
    pongo las imágenes de los dos árboles utlizados en la carpeta. Y la prueba supone
    que el algoritmo está bien si el árbol permanece estando ordenado (se imprime). */

    //Inicia árbol
    RBTree *tree;
    tree = newRBTree();
    int i;


    //Caso 1: el hermano del nodo que se quiere borrar es rojo
    i = 10;
    put(tree, i, i);
    i = 7;
    put(tree, i, i);
    i = 8;
    put(tree, i, i);
    i = 3;
    put(tree, i, i);
    i = 15;
    put(tree, i, i);
    i = 11;
    put(tree, i, i);
    i = 20;
    put(tree, i, i);
    i = 21;
    put(tree, i, i);

    printf("\n *--------Antes de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    //Borra al nodo
    i = 7;
    deleteNode(tree,i);

    printf("\n *--------Después de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);

    printf("\n *----------------------------- *\n");
    inOrderFreeTree(tree, tree->root);
    tree = newRBTree();
    //Caso 2: el hermano del nodo que se quiere borrar es negro y los dos hijos del hermano son negros
    i = 50;
    put(tree, i, i);
    i = 100;
    put(tree, i, i);
    i = 60;
    put(tree, i, i);
    i = 500;
    put(tree, i, i);
    i = 90;
    put(tree, i, i);
    i = 65;
    put(tree, i, i);
    i = 95;
    put(tree, i, i);
    i = 110;
    put(tree, i, i);
    i = 120;
    put(tree, i, i);
    i = 95;
    put(tree, i, i);
    i = 98;
    put(tree, i, i);

    printf("\n *--------Antes de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    //Borra al nodo
    i = 60;
    deleteNode(tree,i);

    printf("\n *--------Después de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    printf("\n *----------------------------- *\n");

    inOrderFreeTree(tree, tree->root);
    tree = newRBTree();

    //Caso 3: el hermano del nodo que se quiere borrar es negro y uno de los hijos del hermano es rojo y otro negro
    i = 50;
    put(tree, i, i);
    i = 100;
    put(tree, i, i);
    i = 60;
    put(tree, i, i);
    i = 500;
    put(tree, i, i);
    i = 90;
    put(tree, i, i);
    i = 65;
    put(tree, i, i);
    i = 95;
    put(tree, i, i);
    i = 110;
    put(tree, i, i);
    i = 120;
    put(tree, i, i);
    i = 95;
    put(tree, i, i);
    i = 98;
    put(tree, i, i);

    printf("\n *--------Antes de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    //Borra al nodo
    i = 150;
    deleteNode(tree,i);

    printf("\n *--------Después de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    printf("\n *----------------------------- *\n");

    inOrderFreeTree(tree, tree->root);
    tree = newRBTree();

    //Caso 4: el hermano del nodo que se quiere borrar es negro y los hijos del hermano son rojos
    i = 10;
    put(tree, i, i);
    i = 7;
    put(tree, i, i);
    i = 8;
    put(tree, i, i);
    i = 3;
    put(tree, i, i);
    i = 15;
    put(tree, i, i);
    i = 11;
    put(tree, i, i);
    i = 20;
    put(tree, i, i);
    i = 21;
    put(tree, i, i);

    printf("\n *--------Antes de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    //Borra al nodo
    i = 15;
    deleteNode(tree,i);

    printf("\n *--------Después de borrar--------- *\n");
    inOrderPrintTree(tree, tree->root);
    printf("\n *----------------------------- *\n");
    inOrderFreeTree(tree, tree->root);

    return 1;
}



