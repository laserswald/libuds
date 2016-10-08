/* list.c
 *
 * A basic doubly linked list implementation.
 */ 
#include "stdio.h"
#include "stdlib.h"
#include "dllist.h"

// Basic node operations.
static struct dlnode* dlnode_new(void* item){
    struct dlnode* n = malloc(sizeof(struct dlnode));
    n->prev = NULL;
    n->next = NULL;
    n->data = item;
    return n;
}

int dlnode_free(struct dlnode *target){
    free(target);
    return 0;
}

// Connect two dlnodes in a specific order
void dlnode_connect(struct dlnode *first, struct dlnode *second){
    if (first != NULL) first->next = second;
    if (second != NULL) second->prev = first;
}

// Disconnect a node from it's neighbors
void dlnode_disconnect(struct dlnode *node){
    if (!node) return;

    // Neighbors no longer know about this one.
    if (node->next){
        node->next->prev = NULL;
    }
    if (node->prev){
        node->prev->next = NULL;
    }

    // This node no longer knows about it's neighbors
    node->prev = NULL;
    node->next = NULL;
}

/// List operations. Should just be basic wrappers around the node operations.

dllist* dllist_new(){
    dllist* this = (dllist*)malloc(sizeof(dllist));
    // Extra construction stuff....
    this->head = NULL;
    this->tail = NULL;
    return this;
}

// Destroys the linked list.
void dllist_free(dllist* list)
{
    if (!list) return;

    struct dlnode* index = list->head;
    struct dlnode* previous = NULL;
    while (index){
        previous = index;
        index = index->next;
        free(previous);
    }

}


int dllist_append(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = dlnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (dllist_isempty(l)){
        l->head = elem;
        l->tail = elem;
    } else {
        dlnode_connect(l->tail, elem);
        l->tail = elem;
    }
    return 0;
}

int dllist_push(dllist* l, void* item){
    if (!l) { 
        puts("dllist does not exist");
        return 1;
    }

    struct dlnode* elem = dlnode_new(item);
    if (!elem) {
        puts("element could not be created: no more memory");
    }

    // No head of list, there is no list.
    if (dllist_isempty(l)){
        l->head = l->tail = elem;
    } else {
        dlnode_connect(elem, l->head);
        l->head = elem;
    }

    return 0;
}

void* dllist_pop(dllist* l){
    if (!l) { 
        puts("list does not exist");
        return NULL;
    }

    struct dlnode* prevHead = l->head;
    if (prevHead == NULL) return NULL;
    void* data = prevHead->data;

    l->head = prevHead->next;

    dlnode_disconnect(prevHead);

    return data;
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
    if (prevTail == NULL) return NULL;

    void* data = prevTail->data;
    l->tail = prevTail->prev;
    dlnode_disconnect(prevTail);

    return data;
}




