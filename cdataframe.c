#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "cdataframe.h"
#include "column.h"


#if 0
CDATAFRAME* cdf_create(ENUM_TYPE *cdftype, int size)
{
    CDATAFRAME* newCdf = (CDATAFRAME*)malloc(sizeof(CDATAFRAME));
    return newCdf;
}

void cdf_delete(CDATAFRAME** cdf)
{
    list_delete(*cdf);
    free(cdf);
}

COLUMN* cdf_get_column(CDATAFRAME* cdf, int column)
{
    NODE* node = list_get(cdf, column);
    COLUMN* result = node->data;
    return result;
}

int cdf_rows_count(CDATAFRAME* cdf)
{
    if (cdf->first == NULL || cdf->first->data->data == NULL) return 0;
    return 1;
}
#endif