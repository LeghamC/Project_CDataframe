#ifndef CDATAFRAME_SORT_H
#define CDATAFRAME_SORT_H

#include "column.h"

#define ASC 0
#define DESC 1


void insertion_sort(COLUMN* col, int sort_dir);
void quick_sort(COLUMN* col, int sort_dir);



#endif //CDATAFRAME_SORT_H
