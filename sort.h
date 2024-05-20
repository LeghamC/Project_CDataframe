#ifndef CDATAFRAME_SORT_H
#define CDATAFRAME_SORT_H

#include "column.h"

#define ASC 0
#define DESC 1

int compare(COLUMN_TYPE* val1, COLUMN_TYPE* val2, ENUM_TYPE type);
void insertion_sort(COLUMN* col, int sort_dir);
void swap(COLUMN_TYPE** p1, COLUMN_TYPE** p2);
int partition(COLUMN* col, int low, int high, int sort_dir);
void quick_sort(COLUMN* col, int low, int high, int sort_dir);
void sort(COLUMN* col, int sort_dir);


#endif
