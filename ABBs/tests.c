#include "abb.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_put_element(void);

int main(int num_args, char ** args){
  int all_tests_ok = 1;
  all_tests_ok &= test_put_element();
  assert(all_tests_ok);
  return 0;
}

int test_put_element(void){
  printf("*- Test Put Element -*\n");
  // Create RBT
  RBTree *trial;
  trial = newRBTree();
  put(trial,2,50);
  put(trial,14,3);
  put(trial,1,100);
  put(trial,7,97);

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

