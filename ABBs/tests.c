#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

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
  ABBNode *trial;
  trial = newABBNode(10,2);
  
  free_THeap(&trial);
  puts("OK");
  return 1;
}