#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

//Auxiliares para visualizar
void inOrderPrintTree(RBTree *tree, ABBNode* root);
void showsubtree(RBTree *tree, ABBNode *root, int space);
void showRBT(RBTree *tree,ABBNode *root);

//Tests
int test_put_element(void);
int test_delete_element(void);





#endif // TESTS_H_INCLUDED
