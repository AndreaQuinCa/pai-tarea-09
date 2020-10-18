#include <stdio.h>
#include <stdlib.h>

typedef struct ABBNodeStruct{
    struct ABBNodeStruct* left;
    struct ABBNodeStruct* right;
    struct ABBNodeStruct* parent;
    int data;
    int key;
    int color; //0 negro, 1 rojo
}ABBNode;


ABBNode* newABBNode(int key, int val){
    //Inicializa nuevo nodo
    ABBNode* z = (ABBNode*) malloc(sizeof(ABBNode));
    if(z == NULL){
        printf("No se concedio memoria para nuevo nodo\n");
        return NULL;
    }
    z->left   = NULL;
    z->right  = NULL;
    z->parent = NULL;
    z->color  = 1;    //Color igual a rojo
    z->data   = val;
    z->key    = key;
    return z;
}

//O(1)
void leftRotate(ABBNode* root, ABBNode* x){
/*Toma la raíz de un subárbol lo rota hacia la izquierda*/
    if(x->right == NULL){
        printf("La rotacion del nodo x=%d, en invalida\n", x->key);
        return;
    }
    ABBNode* y = x->right;

    //El hijo izquierdo de y se vuelve el hijo derecho de x
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;

    //Vincula a y con el padre de x
    if(x->parent == NULL){
        root = y;
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
void rightRotate(ABBNode* root, ABBNode* x){
/*Toma la raíz de un subárbol lo rota hacia la derecha*/
    if(x->left == NULL){
        printf("La rotacion del nodo x=%d, en invalida\n", x->key);
        return;
    }
    ABBNode* y = x->left;

    //El hijo derecho de y se vuelve el hijo izquierdo de x
    x->left = y->right;
    if(y->right != NULL){
        y->right->parent = x;
    }
    y->parent = x->parent;

    //Vincula a y con el padre de x
    if(x->parent==NULL){
        root = y;
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

void fixPut(ABBNode* root, ABBNode* z){
    /*Corrige las propiedades de ABB que se pudieron
    haber violado al insertar el nuevo nodo*/

    //Sólo había un nodo
    if(root->parent == NULL){
        root->color = 0;
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
            else if(z == z->parent->right){
                z = z->parent;
                leftRotate(root, z);
            }
            z->parent->color         = 0;
            z->parent->parent->color = 1;
            rightRotate(root, z->parent->parent);
        }
        //Caso en el que el papá es el hijo derecho del abuelo
        if(z->parent == z->parent->parent->right){
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
            else if(z == z->parent->left){
                z = z->parent;
                rightRotate(root, z);
            }
            z->parent->color         = 0;
            z->parent->parent->color = 1;
            leftRotate(root, z->parent->parent);
        }
    }
    root->color = 0;
}

void put(ABBNode* root, int key, int val){
    /*Inserta un par en el árbol, si la llave existe
    el valor anterior se reemplaza por val, sino, se
    agrega en una hoja. Regresa un apuntador a la nueva
    raíz.*/

    //Busca al padre como en un árbol de búsqueda sencillo
    ABBNode* y = NULL; //Auxiliar para guardar al padre
    ABBNode* x = root; //Variable para avanzar en el árbol
    while(x != NULL){
        y = x;
        if(key < root->key){
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

    ABBNode*z = newABBNode(key, val);
    z->parent = y;
    if(y!= NULL && key<y->key){
        y->left = z;
    }
    else if(y!= NULL && key>y->key){
        y->right = z;
    }

    fixPut(root, z);
    return;
}
/* ********************** Funciones para Delete ********************** */
void transplant(ABBNode* root, ABBNode* x, ABBNode* y){
    if (x->parent == NULL){
        root = y;
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

void deletefixput(ABBNode* root, ABBNode* x){
    ABBNode* w = NULL;
    while (x->parent != NULL && x->color == 0){
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
            if (w->left->color == 0 && w->right->color ==0){
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
            x = root;
        }
        
        if (x == x->parent->right){
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
                w->color = 1;
                leftRotate(root, w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = 0;
            w->left->color  = 0;
            rightRotate(root,x->parent);
            x = root;
        }
    }
    x->color = 0;
    return;
}

ABBNode *minimum(ABBNode *x){
    while (x->right != NULL){
        x = x->left;
    }
    return x;
}

void delete(ABBNode* root, ABBNode* z){
    ABBNode* y = NULL; // Nodo Auxiliar
    ABBNode* x = NULL; // Nodo Auxiliar

    y = z;
    int y_original_color = y->color;
    if (z->left == NULL){
        x = z->right;
        transplant(root,z,z->right);
    }
    else if (z->right == NULL){
        x = z->left;
        transplant(root,z,z->left);
    }
    else{
        y = minimum(z->right);
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
    return;
}

/* ********************** Funciones Especiales ********************** */
int get(ABBNode* root, int key){
    ABBNode* x = root;               //Variable para avanzar en el árbol
    
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

int contains(ABBNode* root, int key){
    ABBNode* x = root;          //Variable para avanzar en el árbol

    while(x != NULL){
        if(key == root->key){
            return 1;
        }
        else if(key > x->key) {      // Busco en la Derecha
            x = x->right;
        }
        else{
            x->data = key;           // Busco en la Izquierda
        }
    }
    return 0;
}

int isEmpty(ABBNode* root){
    return root == NULL;
}

int size(ABBNode* root){
    if (root->left == NULL || root->right == NULL) {
        return 1;
    }

    int left_size  = size(root->left);
    int right_size = size(root->right);
    if (left_size > right_size){
        return left_size+1;
    }
    else{
        return right_size+1;
    }
}

int blacksize(ABBNode *root){

}
