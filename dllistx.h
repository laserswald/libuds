#ifndef __UDS_EXTRA_DLLIST

#define __UDS_EXTRA_DLLIST

#include "dllist.h"
#include "funcdefs.h"

dllist* dllist_map(dllist* list, void* (*fn)(void*));

dllist* dllist_filter(dllist* list, fn_pred);

int dllist_do(dllist*, void (*fn)(void*));

// Merge sorts the list with the given comparison function.
struct dllist* dllist_sort(dllist*, fn_cmp);

#endif /* end of include guard: __UDS_EXTRA_DLLIST */
