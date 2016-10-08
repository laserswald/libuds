/* list.c
 *
 * A basic doubly linked list implementation.
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "dllist.h"


static struct dlnode* listnode_new(void* item){
    struct dlnode* n = malloc(sizeof(struct dlnode));
    n->prev = NULL;
    n->next = NULL;
    n->data = item;
    return n;
}

dllist* dllist_new(){
    dllist* this = (dllist*)malloc(sizeof(dllist));
    // Extra construction stuff....
    this->head = NULL;
    this->tail = NULL;
    return this;
}


int destroy_node(struct dlnode* target){
    free(target);
    return 0;
}

int dllist_append(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = listnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (l->head == NULL && l->tail == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        l->tail->next = elem;
        elem->prev = l->tail;
        l->tail = elem;
    }

    l->length = l->length + 1;
    return 0;

    error:
    if (elem) destroy_node(elem);
    return 1;
}

int dllist_push(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = listnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (l->head == NULL){
        l->head = elem;
        l->tail = elem;
    } else {
        l->head->prev = elem;
        elem->next = l->head;
        l->head = elem;
    }

    l->length = l->length + 1;
    return 0;

    error:
    if (elem) destroy_node(elem);
    return -1;
}

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

void* dllist_pop(dllist* l){
    //return dllist_remove(list, 0);
    //TODO: Make sure the list is fine
    if (!l) { 
        puts("list does not exist");
        return NULL;
    }

    // TODO: make sure the head is okay
    struct dlnode* prevHead = l->head;
    if (prevHead == NULL) goto error;
    void* data = prevHead->data;
    l->head = prevHead->next;
    if (l->head)
        l->head->prev = NULL;
    l->length = l->length - 1;
    return data;
error:
    return NULL;
}

void* dllist_retrieve(dllist* l){
    //return dllist_remove(list, 0);
    //TODO: Make sure the list is fine
    if (!l) { 
        puts("list does not exist");
        return NULL;
    }

    // TODO: make sure the head is okay
    struct dlnode* prevTail = l->tail;
    if (prevTail == NULL) goto error;
    void* data = prevTail->data;
    l->tail = prevTail->prev;
    if (l->tail)
        l->tail->next = NULL;
    l->length = l->length - 1;
    return data;
error:
    return NULL;
}


dllist* merge(dllist* l, dllist* r, int (*cmp)(void*, void*)){
    dllist* ret = dllist_new();
    void *lval = dllist_pop(l);
    void *rval = dllist_pop(r);
    while (l->length != 0 || r->length != 0){ 
        if (lval == NULL && rval == NULL) {
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
    // Choose the center value.
    if (list == NULL) return NULL;
    if (list->length == 0) return NULL; 
    if (list->length == 1) return list;
    int middle = list->length / 2;
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


// Destroys the linked list.
int dllist_free(dllist* list)
{
    if (!list) return -1;
    
    struct dlnode* index = list->head;
    struct dlnode* previous = NULL;
    while (index){
        previous = index;
        index = index->next;
        free(previous);
    }
    return 0;
}

