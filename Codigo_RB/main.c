#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "abb.h"
#include "tests.h"

int main()
{
    int all_tests_ok = 1;
    all_tests_ok &= test_put_element();
    all_tests_ok &= test_delete_element();
    assert(all_tests_ok);
    return 0;
}
