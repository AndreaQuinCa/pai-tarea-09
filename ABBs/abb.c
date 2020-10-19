#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

//estructuras en archivo .h

ABBNode* newABBNode(int key, int val){
    //Inicializa nuevo nodo
    ABBNode* z = (ABBNode*) malloc(sizeof(ABBNode));
    if(z == NULL){
        printf("No se concedio memoria para nuevo nodo\n");
        return NULL;
    }
    z->color  = 1;    //Color igual a rojo
    z->data   = val;
    z->key    = key;
    z->left   = NULL;
    z->right  = NULL;
    z->parent = NULL;
    return z;
}

RBTree* newRBTree(){
    RBTree *newtree = (RBTree*) malloc (sizeof(RBTree));
    if(newtree == NULL){
        printf("No se concedio memoria para el arbol\n");
        return NULL;
    }
    // Definicion de NIL
    newtree->nil = newABBNode(0,0);
    newtree->nil->color = 0;
    // Atributos del arbol
    newtree->root = newtree->nil;
    newtree->size = 0;
    return newtree;
}

void freeNode(ABBNode **z){
    (*z)->left   = NULL;
    (*z)->right  = NULL;
    (*z)->parent = NULL;
    free(*z);
    *z = NULL;
}

//Auxiliares
int isEmpty(RBTree* root){
    if (root == NULL){
        return 1;
    }
    else if(root->root == root->nil){
        return 1;
    }
    return 0;
}

int contains(RBTree* root, int key){
    ABBNode* x;          //Variable para avanzar en el árbol
    if (isEmpty(root) == 1){
        printf("Árbol vacío.\n");
        return 0;
    }
    x = root->root;
    while(x != NULL){
        if(x->key == key){
            return 1;
        }
        else if(key > x->key) {      // Busco en la Derecha
            x = x->right;
        }
        else{
            x = x->left;           // Busco en la Izquierda
        }
    }
    freeNode(&x);
    return 0;
}

int size(RBTree* root){
    return root->size;
}

//Put
void leftRotate(RBTree* root, ABBNode* x){
/*Toma la raíz de un subárbol lo rota hacia la izquierda*/
    ABBNode* y = x->right;
    //El hijo izquierdo de y se vuelve el hijo derecho de x
    x->right = y->left;
    if(y->left != root->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;

    //Vincula a y con el padre de x
    if(x->parent == root->nil){
        root->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }

    //Establece a x hijo de y
    y->left   = x;
    x->parent = y;

}

//O(1)
void rightRotate(RBTree* root, ABBNode* x){
/*Toma la raíz de un subárbol lo rota hacia la derecha*/
    ABBNode* y = x->left;

    //El hijo derecho de y se vuelve el hijo izquierdo de x
    x->left = y->right;
    if(y->right != root->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;

    //Vincula a y con el padre de x
    if(x->parent == root->nil){
        root->root = y;
    }
    else if(x == x->parent->right){
        x->parent->right = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }

    //Establece a x hijo de y
    y->right  = x;
    x->parent = y;
}

void fixPut(RBTree* root, ABBNode* z){
    /*Corrige las propiedades de ABB que se pudieron
    haber violado al insertar el nuevo nodo*/
    if(z->parent == root->nil){
        z->color = 0;
        return;
    }
    //Sólo hay que hacer modificaciones si el padre
    //del nuevo nodo es rojo
    while(z->parent->color == 1){
        //Caso en el que el papá es el hijo izquierdo del abuelo
        if(z->parent == z->parent->parent->left){
            ABBNode* y = z->parent->parent->right; //Tío
            //Caso en el que el tío es rojo, se intercambian los colores
            if(y->color == 1){
                z->parent->color         = 0;
                y->color                 = 0;
                z->parent->parent->color = 1;
                z                        = z->parent->parent;
                //Se puede provocar una violación al nivel del abuelo
            }
            //Caso en el que el tío es negro, se corrige con rotaciones
            else{
                if(z == z->parent->right){
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color         = 0;
                z->parent->parent->color = 1;
                rightRotate(root, z->parent->parent);
            }
        }
        //Caso en el que el papá es el hijo derecho del abuelo
        else{
            ABBNode* y = z->parent->parent->left; //Tío
            //Caso en el que el tío es rojo, se intercambian los colores
            if(y->color==1){
                z->parent->color         = 0;
                y->color                 = 0;
                z->parent->parent->color = 1;
                z                        = z->parent->parent;
                //Se puede provocar una violación al nivel del abuelo
            }
            //Caso en el que el tío es negro, se corrige con rotaciones
            else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(root, z);
                }

            z->parent->color         = 0;
            z->parent->parent->color = 1;
            leftRotate(root, z->parent->parent);
            }
        }
    }
    root->root->color = 0;
}

void put(RBTree* root, int key, int val){
    /*Inserta un par en el árbol, si la llave existe
    el valor anterior se reemplaza por val, sino, se
    agrega en una hoja. Regresa un apuntador a la nueva
    raíz.*/
    //Busca al padre como en un árbol de búsqueda sencillo
    ABBNode* y = root->nil; //Auxiliar para guardar al padre
    ABBNode* x = root->root; //Variable para avanzar en el árbol
    while(x != root->nil){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else if(key > x->key) {
            x = x->right;
        }
        else{
            x->data = val; //La llave ya existía
            return;
        }
    }
    //La decalración se necesita aquí en caso de que la llave exista
    ABBNode* z = newABBNode(key, val);
    if(z==NULL){
        printf("Problemas con el nuevo nodo key=%d val=%d\n", key, val);
        return;
    }

    z->parent = y;
    if (y == root->nil) {
        root->root = z;
    }
    else if (z->key < y->key){
        y->left = z;
    }
    else {
        y->right = z;
    }
    // Apunto a NIL
    z->left  = root->nil;
    z->right = root->nil;
    fixPut(root, z);
    root->size++;
}

//Delete
void transplant(RBTree* root, ABBNode* x, ABBNode* y){
    if (x->parent == root->nil){
        root->root = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->parent = x->parent;
    return;
}

void deletefixput(RBTree* root, ABBNode* x){
    ABBNode* w;
    while (x != root->root && x->color == 0){
        if (x == x->parent->left){
            w = x->parent->right;
            // Caso 1
            if (w->color == 1){
                w->color         = 0;
                x->parent->color = 1;
                leftRotate(root,x->parent);
                w = x->parent->right;
            }
            // Caso 2
            if (w->left->color == 0 && w->right->color == 0){
                w->color == 1;
                x = x->parent;
            }
            // Caso 3
            else if (w->right->color == 0){
                w->left->color = 0;
                w->color = 1;
                rightRotate(root, w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 0;
            w->right->color  = 0;
            leftRotate(root,x->parent);
            x = root->root;
        }

        else {
            w = x->parent->left;
            // Caso 1
            if (w->color == 1){
                w->color         = 0;
                x->parent->color = 1;
                rightRotate(root,x->parent);
                w = x->parent->left;
            }
            // Caso 2
            if (w->right->color == 0 && w->left->color == 0){
                w->color == 1;
                x = x->parent;
            }
            // Caso 3
            else if (w->left->color == 0){
                w->right->color = 0;
                w->color        = 1;
                leftRotate(root, w);
                w = x->parent->left;
            }
            w->color         = x->parent->color;
            x->parent->color = 0;
            w->left->color   = 0;
            rightRotate(root,x->parent);
            x = root->root;
        }
    }
    x->color = 0;
    return;
}

ABBNode *minimum(RBTree *tree, ABBNode *root){
    ABBNode* min = root;      // inicializo minimo
    while (min->left != tree->nil){
        min = min->left;
    }
    return min;
}

int getData(RBTree* root, int key){
    ABBNode* x;               //Variable para avanzar en el árbol
    if (isEmpty(root) != 0){
        printf("Árbol vacío.\n");
        return -1;
    }
    x = root->root;
    while(x != NULL){
        if(key == x->key){
            return x->data;
        }
        else if(key > x->key) {      // Busco en la derecha
            x = x->right;
        }
        else{
            x = x->left;           // Busco en la Izquierda
        }
    }
    return -1;
}

ABBNode *getNode(RBTree *root, int key){
    ABBNode* x;                      // Variable para avanzar en el árbol
    if (isEmpty(root) != 0){
        printf("Árbol vacío.\n");
        return root->nil;
    }
    x = root->root;
    while(x != NULL){
        if(key == x->key){
            return x;
        }
        else if(key > x->key) {      // Busco en la derecha
            x = x->right;
        }
        else{
            x = x->left;           // Busco en la Izquierda
        }
    }
    return root->nil;
}

void deleteNode(RBTree* root, int key){
    if (getData(root,key) == -1) return; // Reviso que exista llave
    
    ABBNode* z = getNode(root,key);
    ABBNode* y = NULL;                  // Nodo Auxiliar
    ABBNode* x = NULL;                  // Nodo Auxiliar
    y = z;
    int y_original_color = y->color;

    if (z->left == root->nil){
        x = z->right;
        transplant(root,z,z->right);
    }
    else if (z->right == root->nil){
        x = z->left;
        transplant(root,z,z->left);
    }
    else{
        y = minimum(root,z->right);
        y_original_color = y->color;
        x                = y->right;
        if (y->parent == z){
            x->parent = y;
        }
        else{
            transplant(root,y,y->right);
            y->right         = z->right;
            y->right->parent = y;
        }
        transplant(root,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == 0){
        deletefixput(root,x);
    }
    printf("Se borró correctamente nodo  con llave %i.\n", z->key);
    freeNode(&z);
}
