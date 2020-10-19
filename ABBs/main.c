#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abb.h"
#include "tests.h"

int main(int num_args, char ** args){
  int all_tests_ok = 1;
  all_tests_ok &= test_put_element();
  assert(all_tests_ok);
  return 0;
}
