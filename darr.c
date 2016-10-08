// darray.c
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "darr.h"


darr* darr_new(int ispace, size_t datasize){
    darr* array = malloc(sizeof(darr));
    darr_init(array, ispace, datasize);
    return array;
}

darr* darr_init(darr* array, int ispace, size_t datasize){
    array->space = ispace;
    array->data_size = datasize;
    array->arr = calloc(ispace, datasize);
    array->length = 0;
}

int darr_free(darr* array){
    free(array->arr);
    free(array);
    return 0;
}

/**
 *  Goes through the array and destroys everything in the array using the
 *  given function.
 */
int darr_destroy(darr* array, int (*destroyfn)(void*)){
    if (!array) return -1;
    if (!array->arr) return -1;

    // Go through the array, calling the destroy function. 
    int i;
    for(i = 0; i < array->space; i++){
        if (!destroyfn(darr_get(array, i))){
            return -1;
        }
    }
    darr_free(array);
    return 0;
}


int darr_resize(darr* array, size_t newsize){
    // TODO: Make sure this is unbreakable.
    if (!array) return -1;
    if (!array->arr) return -1;

    assert(newsize < array->length);
    assert(newsize < array->space); 

    array->arr = realloc(array->arr, newsize*array->data_size);

    if (!array->arr) return -1;
    
    array->space = newsize;
    return 0;
}

int darr_set(darr* array, int index, void* item){
    if (!array) return -1;
    if (!array->arr) return -1;
    
    if (index > array->space){
        int status = darr_resize(array, (array->space)*2);
        if (status != 0){
            return -1;
        }
    }

    array->arr[index] = item;    

    if (index == array->length) array->length++;
    return 0;
}

void* darr_get(darr* array, int index){
    if (!array) return NULL;
    if (!array->arr) return NULL;
    
    if (index < 0) return NULL;
    if (index > array->space) return NULL;

    return (array->arr)[index];
}
