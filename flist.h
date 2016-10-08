#ifndef FLIST_H
#define FLIST_H
#include "mindata.h"

#define flist_s(type) \
struct flist_##type { \
    type * data; \
    struct flist_##type* next;  \
}

#define flist(type) struct flist_ ## type

#define

#endif /* end of include guard: FLIST_H */
