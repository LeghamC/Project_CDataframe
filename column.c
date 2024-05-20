/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's column's file - implement functions and operations to
               manage and manipulate individual columns used in the dataframe
----------------------------------------------------------------------------------------- **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "column.h"
#include "vector.h"

/**
 * @brief: Creates an empty column with the given title
 * @param1: The type of the values of the column
 * @param2: The title of the column
 * @return: A pointer to the new column
 */

COLUMN* col_create(ENUM_TYPE type, char* title)
{
    COLUMN* newCol = (COLUMN*)malloc(sizeof(COLUMN));
    newCol->title = title;
    newCol->pSize = 0;
    newCol->lSize = 0;
    newCol->type = type;
    newCol->data = NULL;
    newCol->validIndex = 0;
    newCol->sortDir = 0;
    return newCol;
}

/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int col_insert_value(COLUMN *col, void *value)
{
    // Check the pointers
    if (col == NULL) return 0;

    // Check if there is a need to resize
    if (col->lSize >= col->pSize)
    {
        // Add the REALLOC_SIZE to the size of the array
        unsigned int new_pSize = (col->pSize) + REALLOC_SIZE;

        COLUMN_TYPE** newData;
        if (col->pSize == 0) newData = malloc(new_pSize * sizeof(void *));
        else newData = realloc(col->data, new_pSize * sizeof(void *));
        if (newData == NULL) return 0;

        col->data = newData;
        col->pSize = new_pSize;
    }

    // Insert the values by column's type
    switch (col->type)
    {
        case UINT:
            // Allocation for uint values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the uint value into allocated memory
            (col->data)[col->lSize]->uint_value = *((unsigned int *) value);
            break;

        case INT:
            // Allocation for int values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the int value into allocated memory
            (col->data)[col->lSize]->int_value = *((int *) value);
            break;

        case CHAR:
            // Allocation for character values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the character value into allocated memory
            (col->data)[col->lSize]->char_value = *((char *) value);
            break;

        case FLOAT:
            // Allocation for float values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the float value into allocated memory
            (col->data)[col->lSize]->float_value = *((float *) value);
            break;

        case DOUBLE:
            // Allocation for double values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the double value into allocated memory
            (col->data)[col->lSize]->double_value = *((double *) value);
            break;

        case STRING:
            // Allocation for string values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            col->data[col->lSize]->string_value = malloc(STR_LENGTH * sizeof(char));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the string value into allocated memory
            // strncpy instead of strcpy to prevent buffer with more characters than allowed by STR_LENGTH
            strncpy((col->data)[col->lSize]->string_value, (char*)value, STR_LENGTH);
            ((char *)(col->data)[col->lSize])[STR_LENGTH] = '\0';
            break;

        case VEC:
        {
            // Allocation for vector type values
            (col->data)[col->lSize] = malloc(sizeof(COLUMN_TYPE));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the vector value into allocated memory
            col->data[col->lSize]->vector_value = (VECTOR *)value;
            break;
        }

        default:
            return 0;
    }

    (col->lSize)++;
    return 1;
}


/**
* @brief: Frees the space allocated to a column
* @param1: Pointer to the column
*/
void col_delete(COLUMN **col)
{
    // Case where there is nothing to delete
    if (col == NULL || *col == NULL) return;

    // Frees memory for col's attributes
    for (int i = 0; i < (*col)->lSize; i++)
    {
        free((*col)->data[i]);
    }

    free((*col)->data);
    free((*col)->title);
    free((*col)->index);
    free(*col);

    *col = NULL;
}


/**
 * @brief Converts the value into a string
 * @param1 A pointer to the column
 * @param2 Position of the value in the column's data array
 * @param3 String in which the value will be written
 * @param4 Maximum size of the string
 */
void col_convert_value(COLUMN* column, unsigned int index, char* str, int size)
{
    switch (column->type) {
        // use of snprintf to limit the length of the string to a specified one and in a specified type
        case UINT:
            snprintf(str, size, "%u", (column->data)[index]->uint_value);
            break;
        case INT:
            snprintf(str, size, "%d", (column->data)[index]->int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", (column->data)[index]->char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%f", (column->data)[index]->float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", (column->data)[index]->double_value);
            break;
        case STRING:
            strncpy(str, (column->data)[index]->string_value, size);
            break;
        case VEC:;
            VECTOR* v = column->data[index]->vector_value;
            snprintf(str, size, "(%f ; %f ; %f)", v->x, v->y, v->z);;
            break;
        default:;
            break;
    }
}


/**
* @brief: Display the content of a column
* @param: A Pointer to the column to display
*/
void col_print(COLUMN* col)
{
    if (col->lSize == 0) {
        printf("The column is empty\n");
        return;
    }

    char* valueString = calloc(STR_LENGTH + 1, sizeof(char));
    for (unsigned int i = 0; i < col->lSize; i ++) {
        col_convert_value(col, i, valueString, STR_LENGTH);
        printf("[%u] %s\n", i, valueString);
    }

    free(valueString);
}


/**
* @brief: Return the value present at a given index in the column
* @param1 A pointer to the column
* @param2 the index of the value we are looking for
* @return A pointer to the value at the given index. Or NULL if the index is out of range
*/
COLUMN_TYPE* col_get_value_at(COLUMN* col, int index)
{
    // Test for index not out of range
    if (index >= 0 && index < col->lSize)
        return col->data[index];
    else
        return NULL;
}


/**
* @brief: Return the number of values greater than the one given in parameter
* @param1 A pointer to the column
* @param2 the value for which we want the number of values that are greater
* @return The number of values greater than the given value
*/
int col_get_number_of_values_greater(COLUMN* col, void* value)
{
    if (col == NULL || value == NULL)
    {
        return 0;
    }

    int num_val_g = 0;

    switch (col->type)
    {
        case UINT:
            for (int i = 0; i < col->lSize; i++) {
                if (col->data[i]->uint_value > *(unsigned int*)value) {
                    num_val_g++;
                }
            }
            break;

        case INT:
            for (int i = 0; i < col->lSize; i++) {
                if (col->data[i]->int_value > *(int*)value) {
                    num_val_g++;
                }
            }
            break;

        case CHAR:
            for (int i = 0; i < col->lSize; i++) {
                if (col->data[i]->char_value > *(char*)value) {
                    num_val_g++;
                }
            }
            break;

        case FLOAT:
            for (int i = 0; i < col->lSize; i++) {
                if (col->data[i]->float_value > *(float*)value) {
                    num_val_g++;
                }
            }
            break;

        case DOUBLE:
            for (int i = 0; i < col->lSize; i++) {
                if (col->data[i]->double_value > *(double*)value) {
                    num_val_g++;
                }
            }
            break;

        case STRING:
            for (int i = 0; i < col->lSize; i++) {
                if (strcmp(col->data[i]->string_value, (char*)value) > 0) {
                    num_val_g++;
                }
            }
            break;

        case VEC:
            for (int i = 0; i < col->lSize; i++) {
                if (vec_magnitude_comparison(col->data[i]->vector_value, (VECTOR*)value) > 0) {
                    num_val_g++;
                }
            }
            break;

        default:
            // Unrecognized column type
            return 0;
    }

    return num_val_g;
}


/**
* @brief: Return the number of values smaller than the one given in parameter
* @param1 A pointer to the column
* @param2 the value for which we want the number of values that are smaller
* @return The number of values smaller than the given value
*/
int col_get_number_of_values_smaller(COLUMN* col, void* value)
{
    if (col == NULL || value == NULL) {
        return 0;
    }

    int num_val_s = 0;

    switch (col->type)
    {
        case UINT:
            for(int i = 0; i < col->lSize; i++)
            {
                if (col->data[i]->uint_value < *(unsigned int*)value)
                    num_val_s++;
            }
            break;

        case INT:
            for(int i = 0; i < col->lSize; i++)
            {
                if (col->data[i]->int_value < *(int*)value)
                    num_val_s++;
            }
            break;

            // Smaller in ASCII order
        case CHAR:
            for(int i = 0; i < col->lSize; i++)
            {
                if (col->data[i]->char_value < *(char*)value)
                    num_val_s++;
            }
            break;

        case FLOAT:
            for(int i = 0; i < col->lSize; i++)
            {
                if (col->data[i]->float_value < *(float*)value)
                    num_val_s++;
            }
            break;

        case DOUBLE:
            for(int i = 0; i < col->lSize; i++)
            {
                if (col->data[i]->double_value < *(double*)value)
                    num_val_s++;
            }
            break;

            // Smaller in ASCII order
        case STRING:
            for(int i = 0; i < col->lSize; i++)
            {
                if (strcmp(col->data[i]->string_value, (char*)value) < 0)
                    num_val_s++;
            }
            break;

            // Smaller in vector's length
        case VEC:
            for (int i = 0; i < col->lSize; i++)
            {
                if (vec_magnitude_comparison(col->data[i]->vector_value, (VECTOR*)value) < 0)
                    num_val_s++;
            }
            break;

        default:
            // Unrecognized column type
            return 0;
    }

    return num_val_s;
}


/**
* @brief: Return the number of values equal to the one given in parameter
* @param1 A pointer to the column
* @param2 the value for which we want the number of values that are equal to it
* @return The number of values equal to the given value
*/
int col_get_number_of_values_equal(COLUMN* col, void* value)
{
    int num_val_e = 0;

    switch (col->type)
    {
        case UINT:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (col->data[i]->uint_value == (*(unsigned int *)value))
                    num_val_e++;
            }
            break;

        case INT:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (col->data[i]->int_value == (*(int *)value))
                    num_val_e++;
            }
            break;

            // smaller in alphabetical order
        case CHAR:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (col->data[i]->char_value == (*(char *)value))
                    num_val_e++;
            }
            break;

        case FLOAT:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (col->data[i]->float_value == (*(float *)value))
                    num_val_e++;
            }
            break;

        case DOUBLE:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (col->data[i]->double_value == (*(double *)value))
                    num_val_e++;
            }
            break;

            // smaller in alphabetical order
        case STRING:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (strcmp(col->data[i]->string_value, (char *)value) == 0)
                    num_val_e++;
            }
            break;

        case VEC:
            for (int i = 0; i < col->lSize; i++) {
                if (vec_comparison(col->data[i]->vector_value, (VECTOR*)value) == 0) {
                    num_val_e++;
                }
            }
            break;

        default:
            // unrecognized column type
            return 0;
    }

    return num_val_e;
}


/**
 * @brief: Display the content of the sorted column
 * @param1: Pointer to column
 */
void col_print_by_index(COLUMN *col)
{
    if (col == NULL || col->data == NULL || col->index == NULL)
        return;

    for (int i = 0; i < col->lSize; i++)
    {
        int sorted_index = col->index[i];

        switch (col->type)
        {
            case UINT:
                printf("[%d] %u\n", i, col->data[sorted_index]->uint_value);
                break;

            case INT:
                printf("[%d] %d\n", i, col->data[sorted_index]->int_value);
                break;

            case CHAR:
                printf("[%d] %c\n", i, col->data[sorted_index]->char_value);
                break;

            case FLOAT:
                printf("[%d] %.2f\n", i, col->data[sorted_index]->float_value);
                break;

            case DOUBLE:
                printf("[%d] %.2lf\n", i, col->data[sorted_index]->double_value);
                break;

            case STRING:
                printf("[%d] %s\n", i, col->data[sorted_index]->string_value);
                break;

            case VEC:
                printf("[%d] (%.2lf, %.2lf, %.2lf)\n", i,
                       col->data[sorted_index]->vector_value->x,
                       col->data[sorted_index]->vector_value->y,
                       col->data[sorted_index]->vector_value->z);
                break;

            default:
                printf("[%d] Unknown type\n", i);
                break;
        }
    }
}


/**
 * @brief: Remove a column's index
 * @param1: Pointer to the column
 */
void col_erase_index(COLUMN *col)
{
    if (col == NULL || col->index == NULL)
        return;

    // Free the memory allocated to the index array
    free(col->index);

    // Set index's pointer to NULL
    col->index = NULL;

    // Update validIndex to 0 (no index)
    col->validIndex = 0;
}


/**
 * @brief: Check an index's presence
 * @param1: Pointer to the column
 * @return: 0: if index does not exist,
 *         -1: if index exists but invalid,
 *          1: if index is correct
 */
int col_check_index(COLUMN *col)
{
    if (col == NULL)
        return 0;

    if (col->index == NULL)
        return 0;

    return col->validIndex;
}


/**
 * @brief: Update the index
 * @param1: Pointer to the column
 */
void col_update_index(COLUMN *col)
{
    if (col->validIndex == 0)
    {
        // Apply quick sort if the column is not sorted
        col_sort(col, col->sortDir); // col->sortDir to determine the order
    }
    else if (col->validIndex == -1)
    {
        // Apply insertion sort if the column is partially sorted
        if (col->sortDir == -1)
        {
            col_insertion_sort(col, DESC);
            col->validIndex = 1; // Mark the index as valid

        }
        else
        {
            col_insertion_sort(col, ASC);
            col->validIndex = 1; // Mark the index as valid
        }
    }
}


/**
* @brief: Check if a value exists in a column
* @param1: Pointer to the column
* @param2: Pointer to the value to search for
* @return: -1: column not sorted,
*           0: value not found
*           1: value found
*/
int col_search_value(COLUMN *col, void *val)
{
    if (col->validIndex != 1)
        return -1; // Column not sorted

    int low = 0;
    unsigned int high = col->lSize - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int comparison = col_compare(col->data[mid], val, col->type);

        // Value found
        if (comparison == 0)
            return 1;

        if (comparison < 0)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return 0; // Value not found
}

/**
 * @brief Compare two values in the column
 * @param val1 Pointer to the first value
 * @param val2 Pointer to the second value
 * @param type type of the values
 * @return -1 if val1 < val2, 1 if val1 > val2, 0 if val1 == val2
 */

int col_compare(COLUMN_TYPE* val1, COLUMN_TYPE* val2, ENUM_TYPE type)
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
void col_insertion_sort(COLUMN* col, int sort_dir)
{
    for (int i = 1; i < col->lSize; i++)
    {
        COLUMN_TYPE* k = col->data[i];
        int j = i - 1;

        // Use compare function and sort_dir to decide order
        while (j >= 0 && ((sort_dir == 1 && col_compare(col->data[j], k, col->type) > 0) ||
                          (sort_dir == -1 && col_compare(col->data[j], k, col->type) < 0)))
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
void col_swap(COLUMN_TYPE** p1, COLUMN_TYPE** p2)
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
int col_partition(COLUMN* col, int low, int high, int sort_dir)
{
    COLUMN_TYPE* pivot = col->data[high];
    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot
        if ((sort_dir == 1 && col_compare(col->data[j], pivot, col->type) < 0) ||
            (sort_dir == -1 && col_compare(col->data[j], pivot, col->type) > 0))
        {
            // Increment index of smaller element
            i++;
            col_swap(&col->data[i], &col->data[j]);
        }
    }
    col_swap(&col->data[i + 1], &col->data[high]);
    return (i + 1);
}

/**
 * @brief: Sort a column using quicksort algorithm
 * @param1: Pointer to the column
 * @param2: Lower bound index
 * @param3: Upper bound index
 * @param4: Sort type (ASC or DESC)
 */
void col_quick_sort(COLUMN* col, int low, int high, int sort_dir)
{
    if (low < high)
    {
        int pi = col_partition(col, low, high, sort_dir);
        col_quick_sort(col, low, pi - 1, sort_dir);
        col_quick_sort(col, pi + 1, high, sort_dir);
    }
}

/**
 * @brief: Sort a column according to a given order
 * @param1: Pointer to the column to sort
 * @param2: Sort type (ASC or DESC)
 */
void col_sort(COLUMN* col, int sort_dir)
{
    if (col == NULL || col->data == NULL || col->lSize <= 1)
        return;

    // Initialize the index array if not already done
    if (col->index == NULL)
    {
        col->index = (unsigned long long*)malloc(col->lSize * sizeof(unsigned long long));
        for (unsigned long long i = 0; i < col->lSize; i++)
        {
            col->index[i] = i;
        }
    }

    if (col->validIndex == 0) // Unsorted column
    {
        col_quick_sort(col, 0, col->lSize - 1, sort_dir);
    }
    else if (col->validIndex == -1) // Partially sorted column
    {
        col_insertion_sort(col, sort_dir);
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