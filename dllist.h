// Minimal C11 linked list
#ifndef __MINLLIST__
#define __MINLLIST__

#include "funcdefs.h"

struct dlnode{
    void* data;
    struct dlnode* prev;
    struct dlnode* next;
};

typedef struct dllist {
    struct dlnode* head;
    struct dlnode* tail;
}dllist;

struct dllist* dllist_new(void);

void dllist_free(dllist*);

// Adds to the back of a list.
int dllist_append(dllist*, void*);

// Gets an item from the back of the list.
void* dllist_retrieve(dllist*);

// Adds to the front of the list.
int dllist_push(dllist*, void*);

// Removes the first element from the list.
void* dllist_pop(dllist*);

#define dllist_isempty(list) ((list)->head == NULL && (list)->tail == NULL)

#endif//LLIST
