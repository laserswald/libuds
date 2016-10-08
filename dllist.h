// Minimal C11 linked list
#ifndef __MINLLIST__
#define __MINLLIST__

#include <stdbool.h>
#include "funcdefs.h"

struct dlnode{
    void* data;
    struct dlnode* prev;
    struct dlnode* next;
};

typedef struct dllist {
    struct dlnode* head;
    struct dlnode* tail;
    int length;
}dllist;

struct dllist* dllist_new(void);

int dllist_free(dllist*);

// Adds to the back of a list.
int dllist_append(dllist*, void*);

// Gets an item from the back of the list.
void* dllist_retrieve(dllist*);

// Adds to the front of the list.
int dllist_push(dllist*, void*);

// Removes the first element from the list.
void* dllist_pop(dllist*);

dllist* dllist_map(dllist* list, vp_trans);

dllist* dllist_filter(dllist* list, fn_p);

int dllist_do(dllist*, );

// Merge sorts the list with the given comparison function.
struct dllist* dllist_sort(dllist*, fn_cmp);

#endif//LLIST
