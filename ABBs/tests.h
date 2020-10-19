#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED


int test_put_element(void);
int test_delete_esteban_element(void);

int inOrderPrintTree(RBTree *tree,ABBNode* root);
void showsubtree(RBTree *tree, ABBNode *root, int space);
void showRBT(RBTree *tree,ABBNode *root);

#endif // TESTS_H_INCLUDED
