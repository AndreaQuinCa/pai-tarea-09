#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

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
void leftRotate(RBTree* root, ABBNode* x);
void rightRotate(RBTree* root, ABBNode* x);
void fixPut(RBTree* root, ABBNode* z);
void put(RBTree* root, int key, int val);
void transplant(RBTree* root, ABBNode* x, ABBNode* y);
void deletefixput(RBTree* root, ABBNode* x);
void deleteNode(RBTree* root, ABBNode* z);
int getData(RBTree* root, int key);
int contains(RBTree* root, int key);
int isEmpty(RBTree* root);
int size(RBTree* root);
int blacksize(RBTree *root);
#endif // ABB_H_INCLUDED
