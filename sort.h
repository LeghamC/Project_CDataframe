#ifndef CDATAFRAME_SORT_H
#define CDATAFRAME_SORT_H

#include "column.h"

#define ASC 0
#define DESC 1

int compare(void* val1, void* val2);
void insertion_sort(COLUMN* col, int sort_dir);
void swap(void** p1, void** p2);
int partition(COLUMN* col, int low, int high);
void quick_sort(COLUMN* col, int low, int high);
void sort(COLUMN* col, int sort_dir);




#endif //CDATAFRAME_SORT_H
