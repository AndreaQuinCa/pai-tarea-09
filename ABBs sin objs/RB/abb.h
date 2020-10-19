#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

//Estructuras
typedef struct ABBNodeStruct{
    struct ABBNodeStruct* left;
    struct ABBNodeStruct* right;
    struct ABBNodeStruct* parent;
    int data;
    int key;
    int color; //0 negro, 1 rojo
}ABBNode;

typedef struct RBTreeStruct{
    ABBNode* root;
    ABBNode* nil;
    int size;
}RBTree;

ABBNode* newABBNode(int key, int val);
RBTree* newRBTree();
void freeNode(ABBNode **z);
void inOrderFreeTree(RBTree *tree, ABBNode* root);

//Auxuliares
int contains(RBTree* root, int key);
int isEmpty(RBTree* root);
int size(RBTree* root);


//Put
void leftRotate(RBTree* root, ABBNode* x);
void rightRotate(RBTree* root, ABBNode* x);
void fixPut(RBTree* root, ABBNode* z);
void put(RBTree* root, int key, int val);

//Delete
void transplant(RBTree* root, ABBNode* x, ABBNode* y);
void deletefixput(RBTree* root, ABBNode* x);
ABBNode *minimum(RBTree *tree, ABBNode *root);
int getData(RBTree* root, int key);
ABBNode *getNode(RBTree *root, int key);
void deleteNode(RBTree* root, int key);


#endif // ABB_H_INCLUDED
