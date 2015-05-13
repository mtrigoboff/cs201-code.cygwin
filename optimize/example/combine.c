#include <stdio.h>
#include "combine.h"

/* Implementation with maximum use of data abstraction */
void combine1 (vec_ptr v, data_t *dest)
{
    int     i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OPER val;
    }
}

/* Move call to vec_length out of loop */
void combine2 (vec_ptr v, data_t *dest)
{
    int     i;
    int     length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OPER val;
    }
}

/* Direct access to vector data */
void combine3 (vec_ptr v, data_t *dest)
{
    int     i;
    int     length = vec_length(v);
    data_t  *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++)
        *dest = *dest OPER data[i];
}

/* Accumulate result in local variable */
void combine4 (vec_ptr v, data_t *dest)
{
    int     i;
    int     length = vec_length(v);
    data_t  *data = get_vec_start(v);
    data_t  x = IDENT;

    for (i = 0; i < length; i++)
        x = x OPER data[i];
    *dest = x;
}

/* Accumulate in local variable, pointer version */
void combine5 (vec_ptr v, data_t *dest)
{
    int     length = vec_length(v);
    data_t  *data = get_vec_start(v);
    data_t  *dend = data+length;
    data_t  x = IDENT;

    for (; data < dend; data++)
        x = x OPER *data;
    *dest = x;
}
