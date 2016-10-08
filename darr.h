#ifndef __DYN_ARRAY
#define __DYN_ARRAY

#include <stdlib.h>

typedef struct darr{
	int length;	// place of the last item in the array (recorded);
	int space; // amount of allocated memory for the array
	size_t data_size; // size of data elements
	void **arr; // pointer to array in memory
}darr;

darr* darr_new(int ispace, size_t datasize);
void darr_init(darr* array, int ispace, size_t datasize);

int darr_free(darr* array);
int darr_destroy(darr* array, int (*destroyfn)(void*));

int darr_set(darr* array, int index, void* item);
void* darr_get(darr* array, int index);

#endif // __DYN_ARRAY
