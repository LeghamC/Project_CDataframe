/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's sort's file - implement sorting algorithms and related functions
               to arrange the data within the columns of the DataFrame.
-----------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sort.h"

/**
 * @brief Compare two values in the column
 * @param val1 Pointer to the first value
 * @param val2 Pointer to the second value
 * @param type type of the values
 * @return -1 if val1 < val2, 1 if val1 > val2, 0 if val1 == val2
 */

int compare(COLUMN_TYPE* val1, COLUMN_TYPE* val2, ENUM_TYPE type)
{
    switch (type)
    {
        case UINT:
        {
            if (val1->uint_value < val2->uint_value) return -1;
            if (val1->uint_value > val2->uint_value) return 1;
            return 0;
        }
        case INT:
        {
            if (val1->int_value < val2->int_value) return -1;
            if (val1->int_value > val2->int_value) return 1;
            return 0;
        }
        case CHAR:
        {
            if (val1->char_value < val2->char_value) return -1;
            if (val1->char_value > val2->char_value) return 1;
            return 0;
        }
        case FLOAT:
        {
            if (val1->float_value < val2->float_value) return -1;
            if (val1->float_value > val2->float_value) return 1;
            return 0;
        }
        case DOUBLE:
        {
            if (val1->double_value < val2->double_value) return -1;
            if (val1->double_value > val2->double_value) return 1;
            return 0;
        }
        case STRING:
        {
            return strcmp(val1->string_value, val2->string_value);
        }
        case VEC:
        {
            return vec_magnitude_comparison(val1->vector_value, val2->vector_value);
        }
        default:
            return 0; // Unknown type or NULLVAL
    }
}


/**
 * @brief: Sort the column using insertion sort algorithm
 * @param1: Pointer to the column to sort
 * @param2: Sort type: ASC or DESC
 */
void insertion_sort(COLUMN* col, int sort_dir)
{
    for (int i = 1; i < col->lSize; i++)
    {
        COLUMN_TYPE* k = col->data[i];
        int j = i - 1;

        // Use compare function and sort_dir to decide order
        while (j >= 0 && ((sort_dir == 1 && compare(col->data[j], k, col->type) > 0) ||
                          (sort_dir == -1 && compare(col->data[j], k, col->type) < 0)))
        {
            col->data[j + 1] = col->data[j];
            j--;
        }
        col->data[j + 1] = k;
    }
}

/**
 * @brief: Swap two COLUMN_TYPE pointers
 * @param1: Pointer to the first COLUMN_TYPE pointer
 * @param2: Pointer to the second COLUMN_TYPE pointer
 */
void swap(COLUMN_TYPE** p1, COLUMN_TYPE** p2)
{
    COLUMN_TYPE* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/**
 * @brief: Partition the column for quicksort
 * @param1: Pointer to the column
 * @param2: Lower bound index
 * @param3: Upper bound index
 * @param4: Sort type: ASC or DESC
 * @return: Partition index
 */
int partition(COLUMN* col, int low, int high, int sort_dir)
{
    COLUMN_TYPE* pivot = col->data[high];
    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot
        if ((sort_dir == 1 && compare(col->data[j], pivot, col->type) < 0) ||
            (sort_dir == -1 && compare(col->data[j], pivot, col->type) > 0))
        {
            // Increment index of smaller element
            i++;
            swap(&col->data[i], &col->data[j]);
        }
    }
    swap(&col->data[i + 1], &col->data[high]);
    return (i + 1);
}

/**
 * @brief: Sort a column using quicksort algorithm
 * @param1: Pointer to the column
 * @param2: Lower bound index
 * @param3: Upper bound index
 * @param4: Sort type (ASC or DESC)
 */
void quick_sort(COLUMN* col, int low, int high, int sort_dir)
{
    if (low < high)
    {
        int pi = partition(col, low, high, sort_dir);
        quick_sort(col, low, pi - 1, sort_dir);
        quick_sort(col, pi + 1, high, sort_dir);
    }
}


/**
 * @brief: Sort a column according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void sort(COLUMN* col, int sort_dir)
{
    if (col == NULL || col->data == NULL || col->lSize <= 1)
        return;

    // Initialize the index array if not already done
    if (col->index == NULL)
    {
        col->index = (unsigned long long *)malloc(col->lSize * sizeof(unsigned long long));
        for (int i = 0; i < col->lSize; i++)
        {
            col->index[i] = i;
        }
    }

    if (col->validIndex == 0) // Unsorted column
    {
        quick_sort(col, 0, col->lSize - 1, sort_dir);
    }
    else if (col->validIndex == -1) // Partially sorted column
    {
        insertion_sort(col, sort_dir);
    }

    // After sorting, mark the column as correctly sorted
    col->validIndex = 1;
    col->sortDir = sort_dir;

    // Update the index array to reflect the sorted order
    for (int i = 0; i < col->lSize; i++)
    {
        col->index[i] = i;
    }
}
