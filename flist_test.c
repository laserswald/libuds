#include <stdio.h>
#include "minunit.h"
#include "flist.h"

flist_s(int);

mu_test(make_flist){
    flist(int)* list = malloc(sizeof(flist(int)));
    flist_int_append();
    return NULL;
}

mu_suite(flist_suite){
    mu_run_test(make_flist);
    return NULL;
}
