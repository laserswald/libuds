#ifndef FUNCDEFS_H
#define FUNCDEFS_H

#include <stdbool.h>
// Void pointer tools
typedef int (*fn_cmp)(void*,void*);
typedef bool (*fn_pred)(void*);

// Generic function to transform a type to itself
typedef void (*fn_free)(void*);

#endif /* end of include guard: FUNCDEFS_H */
