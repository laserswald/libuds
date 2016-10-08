
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dllist.h"
#include "dllistx.h"
#include "minunit.h"

static dllist* list = NULL;
char* first = "one";
char* second = "two";
char* third = "three";
char* testarray[] = {"two", "one", "three"};

char* assertlistvals(dllist* l, char* vals[]){
    struct dlnode* ln = l->head;
    int i = 0;
    for ( ; ln; i++, ln=ln->next){
        mu_streql(vals[i], (char*)ln->data, "dllists are unequal.");
    }  
    return NULL;
}

mu_test(list_alloc_test){
    list = dllist_new();
    mu_assert(list != NULL, "dllist is null.");
    mu_assert(list->head == NULL, "dllist does not nullify head pointer");
    mu_assert(list->tail == NULL, "dllist does not nullify tail pointer");
    return NULL;
}

mu_test(add_get_test){
    dllist_append(list, first);
    char* f = dllist_retrieve(list);
    mu_assert(f == first, "Stored data is not equal to non-stored data");
    return NULL;
}

mu_test(push_pop_test){
    // Test: pop normal use
    char* popped = dllist_pop(list);
    mu_streql(popped, first, "Normal pop use not equal");
    
    // Test: pop on blank list
    popped = dllist_pop(list); 
    mu_assert(popped == NULL, "Pop returned something. That's strange.");
    
    // Test: push on blank list
    dllist_push(list, first);
    mu_assert(list->head->data == first, "Pushing did not happen!");
   
    // Test: push on no list or
    return NULL;
}

void applytestfn(void* v){
    char* item = v; 
    printf("Item: %s\n", item);
}

mu_test(do_test){
    dllist_append(list, first);
    dllist_append(list, third);
    dllist_do(list, &applytestfn); 
    return NULL;
}

int stringcmp(void* a, void* b){
    char* as = a;
    char* bs = b;
    return strcmp(as, bs);
}

mu_test(list_sort_test){
    dllist* sorted = dllist_sort(list, &stringcmp);
    char* sortedarray[] = {"one", "three", "two"};
    assertlistvals(sorted, sortedarray); 
    dllist_free(sorted);
    return NULL;
}

mu_test(list_free_test){
    dllist_free(list);
    return NULL;
}

mu_suite(dllist_suite)
{
    mu_run_test(list_alloc_test);
    mu_run_test(add_get_test);
    mu_run_test(push_pop_test);
    mu_run_test(do_test);
    mu_run_test(list_sort_test);
    mu_run_test(list_free_test);
    return NULL;
}
