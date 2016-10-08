// darr tests

#include <stdlib.h>
#include "minunit.h"
#include "darr.h"

darr* make_int_arr(){
	darr *vec = darr_new(5, sizeof(int));
    return vec;
}

mu_test(darr_get_set){
    darr *arr = make_int_arr();
    int a = 3;
    mu_assert(darr_set(arr, 0, &a) == 0, "Darray_set returned an error.");
    int arrnum = *(int*)(arr->arr[0]);
    mu_assert(arrnum == 3, "Darray item was not returned.");
    arrnum = *(int*)darr_get(arr, 0);
    mu_assert(arrnum == 3, "Darray item was not returned.");
    mu_assert(darr_set(arr, 5, &a) != 0, "darr_set did not prevent boundary check.");
    mu_assert(darr_set(arr, -1, &a) != 0, "darr_set did not prevent negative boundary check.");    

    mu_assert(darr_get(arr, -1) == NULL, "darr_get did not prevent negative index access.");
    mu_assert(darr_get(arr, -5) == NULL, "darr_get did not prevent past the end index access.");
    return NULL;
}

mu_suite(darr_suite){
	mu_run_test(darr_get_set);
    return NULL;
}
