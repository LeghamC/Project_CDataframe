#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sort.h"

/**
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/

int compare(void* val1, void* val2)
// ISSUE : ONLY WORKS FOR INT TYPE VALUES
{
    int elt1 = *(int*)val1;
    int elt2 = *(int*)val2;

    if (elt1 < elt2)
        return -1;

    if (elt1 > elt2)
        return 1;

    return 0;
}


void insertion_sort(COLUMN* col, int sort_dir)
{
    for (int i = 1; i < col->lSize; i++)
    {
        void* k = col->data[i];
        int j = i - 1;

        while (j >= 0 && compare(col->data[j], k) > 0)
        {
            col->data[j + 1] = col->data[j];
            j = j - 1;
        }
        col->data[j + 1] = k;
    }
}


void swap(void** p1, void** p2)
{
    void* temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(COLUMN* col, int low, int high)
{
    void* pivot = col->data[high];

    // Index of smaller element
    // Indicate the right position of pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (compare(col->data[j], pivot) < 0)
        {
            i++;
            swap(&col->data[i], &col->data[j]);
        }
    }
    swap(&col->data[i + 1], &col->data[high]);
    return (i + 1);
}

void quick_sort(COLUMN* col, int low, int high)
{
    if (low < high)
    {
        // pi is the partition return index of pivot
        int pi = partition(col, low, high);

        // Recursion call
        quick_sort(col, low, pi - 1);
        quick_sort(col, pi + 1, high);
    }
}

