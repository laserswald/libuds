#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dllistx.h"

int dllist_do(dllist* list, void (*function)(void*)){
    struct dlnode* current = list->head;
    while(current != NULL){
        (*function)(current->data);
        current = current->next;
    }
    return 0;
}

dllist* dllist_map(dllist* list, void* (*function)(void*)){
    dllist* newlist = dllist_new();
    struct dlnode* current = list->head;
    while(current != NULL){
        dllist_append(newlist, (*function)(current->data));
        current = current->next;
    }
    return newlist;
}

dllist* dllist_filter(dllist* list, bool (*fun)(void*)){
    dllist* newlist = dllist_new();
    struct dlnode* current = list->head;
    while(current != NULL){
        if ((*fun)(current->data)){
            dllist_append(newlist, current->data);
        }
        current = current->next;
    }
    return newlist;
}

dllist* merge(dllist* l, dllist* r, int (*cmp)(void*, void*)){
    dllist* ret = dllist_new();

    void *lval = dllist_pop(l);
    void *rval = dllist_pop(r);

    while (!dllist_isempty(l) || !dllist_isempty(r)){ 
        if (lval == NULL && rval == NULL) {
            // Nothing needs to happen. 
        // Now, if there's only one list left, just get the rest of the list and append it.
        } else if (lval == NULL){
            dllist_append(ret, rval);
        } else if (rval == NULL){
            dllist_append(ret, lval);
        } else {
            // 
            int comparison = cmp(lval, rval);
            if (comparison < 0){
                dllist_append(ret, lval);
                dllist_push(r, rval);
            } else {
                dllist_append(ret, rval);
                dllist_push(l, lval);
            }
        }
    }
    return ret;
}

// Mergesort! 
dllist* dllist_sort(dllist* list, int (*cmp)(void*, void*)){

    if (list == NULL) return NULL;
    if (dllist_isempty(list) || list->head == list->tail){
        return list;
    }

    // Choose the center value.
    //
    int length = 0;
    struct dlnode *cursor = list->head;
    for(length = 0; cursor == list->tail; ++length, cursor = cursor->next);

    int middle = length / 2;
    dllist *left = dllist_new();
    dllist *right = dllist_new();

    struct dlnode* ln = list->head;
    int i = 0;
    while(ln != NULL){
        if(i < middle) dllist_append(left, ln->data); 
        else if (i >= middle) dllist_append(right, ln->data);
        i++;
        ln = ln->next;
    }

    left = dllist_sort(left, cmp);
    right = dllist_sort(right, cmp);
    return merge(left, right, cmp);
}
