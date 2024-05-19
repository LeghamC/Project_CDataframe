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
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/
void insertion_sort(COLUMN* col, int sort_dir)
{
    for (int i = 1; i < col->lSize; i++)
    {
        COLUMN_TYPE* k = col->data[i];
        int j = i - 1;

        // Use compare function and sort_dir to decide order
        while (j >= 0 && ((sort_dir == ASC && compare(col->data[j], k, col->type) > 0) ||
                          (sort_dir == DESC && compare(col->data[j], k, col->type) < 0))) {
            col->data[j + 1] = col->data[j];
            j--;
        }
        col->data[j + 1] = k;
    }
}

/**
* @brief: Sort a column according to a given order
* @param1: Pointer to the column to sort
* @param2: Sort type (ASC or DESC)
*/
void swap(COLUMN_TYPE** p1, COLUMN_TYPE** p2)
{

    COLUMN_TYPE* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


int partition(COLUMN* col, int low, int high)
{
    COLUMN_TYPE* pivot = col->data[high];
    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot
        if (compare(col->data[j], pivot, col->type) == -1)
        {
            // Increment index of smaller element
            i++;
            swap(&col->data[i], &col->data[j]);
        }
    }
    swap(&col->data[i + 1], &col->data[high]);
    return (i + 1);
}

void quick_sort(COLUMN* col, int low, int high, int sort_dir)
{
    if (low < high)
    {
        int pi = partition(col, low, high);

        if (sort_dir == ASC)
        {
            quick_sort(col, low, pi - 1, sort_dir);
            quick_sort(col, pi + 1, high, sort_dir);
        }
        else if (sort_dir == DESC)
        {
            quick_sort(col, low, pi - 1, sort_dir);
            quick_sort(col, pi + 1, high, sort_dir);
        }
    }
}

