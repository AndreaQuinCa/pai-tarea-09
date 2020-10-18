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
  ABBNode *trial;

  trial = newABBNode(10,2);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,10) != 2)   {puts("ERROR"); return 0;}

  put(trial,2,15);
  if(isEmpty(trial) != 0){puts("ERROR"); return 0;}
  if(get(trial,2) != 15)   {puts("ERROR"); return 0;}


  puts("OK");
  return 1;
}