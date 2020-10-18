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

ABBNode* newABBNode(int key, int val);
void leftRotate(ABBNode* root, ABBNode* x);
void rightRotate(ABBNode* root, ABBNode* x);
void fixPut(ABBNode* root, ABBNode* z);
void put(ABBNode* root, int key, int val);
void RBtransplant(ABBNode* root, ABBNode* x, ABBNode* y);

#endif // ABB_H_INCLUDED