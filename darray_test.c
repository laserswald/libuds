// Vector tests

#include <stdlib.h>
#include "minunit.h"
#include "vector.h"

vector* make_int_arr(){
	vector *vec = vector_init(NULL, 5, sizeof(int));
    return vec;
}

mu_test(vector_get_set){
    vector *arr = vector_init(NULL, 5, sizeof(int));
    int a = 3;
    mu_assert(vector_set(arr, 0, &a) == 0, "Darray_set returned an error.");
    int arrnum = *(int*)(arr->arr[0]);
    mu_assert(arrnum == 3, "Darray item was not returned.");
    arrnum = *(int*)vector_get(arr, 0);
    mu_assert(arrnum == 3, "Darray item was not returned.");
    mu_assert(vector_set(arr, 5, &a) != 0, "vector_set did not prevent boundary check.");
    mu_assert(vector_set(arr, -1, &a) != 0, "vector_set did not prevent negative boundary check.");    

    mu_assert(vector_get(arr, -1) == NULL, "vector_get did not prevent negative index access.");
    mu_assert(vector_get(arr, -5) == NULL, "vector_get did not prevent past the end index access.");
    return NULL;
}

mu_suite(darray_suite){
	mu_run_test(vector_get_set);
    return NULL;
}
