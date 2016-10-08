#ifndef FUNCDEFS_H
#define FUNCDEFS_H

// Void pointer tools
typedef void (*fn)(void*) fn_in_trans;
typedef fn_in_trans fn_free;
typedef int (*fn)(void*,void*) fn_cmp;
typedef bool (*fn)(void*) fn_pred;

// Generic function to transform a type to itself
#define fn_trans(type) type (*fn)(type)
typedef fn_trans(void*) vp_trans;

#endif /* end of include guard: FUNCDEFS_H */
