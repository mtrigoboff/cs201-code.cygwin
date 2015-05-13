#ifndef _COMBINE_
#define _COMBINE_

typedef int data_t;

#include "vec.h"

#define IDENT 1
#define OPER  *

// function pointer type definition
typedef void (*CombineFn)(vec_ptr v, data_t *dest);

// function prototypes
void combine1 (vec_ptr v, data_t *dest);
void combine2 (vec_ptr v, data_t *dest);
void combine3 (vec_ptr v, data_t *dest);
void combine4 (vec_ptr v, data_t *dest);
void combine5 (vec_ptr v, data_t *dest);

#endif // _COMBINE_
