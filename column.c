/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's column's file - implement functions and operations to
               manage and manipulate individual columns used in the dataframe
-----------------------------------------------------------------------------------------*/

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

#if 1

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

        COLUMN_TYPE  **newData;
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
            (col->data)[col->lSize] = malloc(sizeof(unsigned int));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the uint value into allocated memory
            *((unsigned int *)(col->data)[col->lSize]) = *((unsigned int *) value);
            break;

        case INT:
            // Allocation for int values
            (col->data)[col->lSize] = malloc(sizeof(int));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the int value into allocated memory
            *((signed int *)(col->data)[col->lSize]) = *((signed int *) value);
            break;

        case CHAR:
            // Allocation for character values
            (col->data)[col->lSize] = malloc(sizeof(char));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the character value into allocated memory
            *((char *)(col->data)[col->lSize]) = *((char *) value);
            break;

        case FLOAT:
            // Allocation for float values
            (col->data)[col->lSize] = malloc(sizeof(float));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the float value into allocated memory
            *((float *)(col->data)[col->lSize]) = *((float *) value);
            break;

        case DOUBLE:
            // Allocation for double values
            (col->data)[col->lSize] = malloc(sizeof(double));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the double value into allocated memory
            *((double *)(col->data)[col->lSize]) = *((double *) value);
            break;

        case STRING:
            // Allocation for string values
            (col->data)[col->lSize] = malloc((STR_LENGTH + 1) * sizeof(char));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the string value into allocated memory
            // strncpy instead of strcpy to prevent buffer with more characters than allowed by STR_LENGTH
            strncpy((char *)(col->data)[col->lSize], (char *) value, STR_LENGTH);
            ((char *)(col->data)[col->lSize])[STR_LENGTH] = '\0';
            break;

        case VEC:
        {
            // Allocation for vector type values
            (col->data)[col->lSize] = malloc(sizeof(VECTOR));
            if ((col->data)[col->lSize] == NULL) return 0;

            // Copy the vector value into allocated memory
            *((VECTOR *)(col->data)[col->lSize]) = *((VECTOR *) value);
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
    char result[size];

    switch (column->type) {
        // use of snprintf to limit the length of the string to a specified one and in a specified type
        case UINT:
            snprintf(str, size, "%u", *((unsigned int*)(column->data)[index]));
            break;
        case INT:
            snprintf(str, size, "%d", *((int*)(column->data)[index]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)(column->data)[index]));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)(column->data)[index]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)(column->data)[index]));
            break;
        case STRING:
            strncpy(str, (char*)(column->data)[index], size);
            break;
        case VEC:
            snprintf(str, size, "%f", *((VECTOR*)(column->data)[index]));
            break;
        case NULLVAL:
            str = "NULL";
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
}

/**
 * @brief: Return the number of occurrences of a given value
 * @param1 A pointer to the column
 * @param2 A pointer to the value for which we want the number of occurrences
 * @return The number of occurrences
 */
int col_occurrences(COLUMN* col, void* value)
{
    if (col == NULL || value == NULL) {
        return 0;
    }

    int occurrence = 0;

    // Occurrence of value based on column's type
    switch (col->type) {
        case UINT:
            for (int i = 0; i < col->lSize; i++) {
                if (*(unsigned int*)col->data[i] == *(unsigned int*)value) {
                    occurrence++;
                }
            }
            break;

        case INT:
            for (int i = 0; i < col->lSize; i++) {
                if (*(int*)col->data[i] == *(int*)value) {
                    occurrence++;
                }
            }
            break;

        case CHAR:
            for (int i = 0; i < col->lSize; i++) {
                if (*(char*)col->data[i] == *(char*)value) {
                    occurrence++;
                }
            }
            break;

        case FLOAT:
            for (int i = 0; i < col->lSize; i++) {
                if (*(float*)col->data[i] == *(float*)value) {
                    occurrence++;
                }
            }
            break;

        case DOUBLE:
            for (int i = 0; i < col->lSize; i++) {
                if (*(double*)col->data[i] == *(double*)value) {
                    occurrence++;
                }
            }
            break;

        case STRING:
            for (int i = 0; i < col->lSize; i++) {
                if (strcmp((char*)col->data[i], (char*)value) == 0) {
                    occurrence++;
                }
            }
            break;

        case VEC:
            for (int i = 0; i < col->lSize; i++) {
                if (vec_comparison((VECTOR*)col->data[i], (VECTOR*)value) == 0) {
                    occurrence++;
                }
            }
            break;

        default:
            // Unrecognized column type
            return 0;
    }

    return occurrence;
}


/**
* @brief: Return the value present at a given index in the column
* @param1 A pointer to the column
* @param2 the index of the value we are looking for
* @return A pointer to the value at the given index. Or NULL if the index is out of range
*/
void* col_get_value_at(COLUMN* col, int index)
{
    // test for index not out of range
    if ((index >= 0) && (index < col->lSize))
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
                if (*(unsigned int*)col->data[i] > *(unsigned int*)value) {
                    num_val_g++;
                }
            }
            break;

        case INT:
            for (int i = 0; i < col->lSize; i++) {
                if (*(int*)col->data[i] > *(int*)value) {
                    num_val_g++;
                }
            }
            break;

        case CHAR:
            for (int i = 0; i < col->lSize; i++) {
                if (*(char*)col->data[i] > *(char*)value) {
                    num_val_g++;
                }
            }
            break;

        case FLOAT:
            for (int i = 0; i < col->lSize; i++) {
                if (*(float*)col->data[i] > *(float*)value) {
                    num_val_g++;
                }
            }
            break;

        case DOUBLE:
            for (int i = 0; i < col->lSize; i++) {
                if (*(double*)col->data[i] > *(double*)value) {
                    num_val_g++;
                }
            }
            break;

        case STRING:
            for (int i = 0; i < col->lSize; i++) {
                if (strcmp((char*)col->data[i], (char*)value) > 0) {
                    num_val_g++;
                }
            }
            break;

        case VEC:
            for (int i = 0; i < col->lSize; i++) {
                if (vec_magnitude_comparison(col->data[i], (VECTOR*)value) > 0) {
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
                if (*(unsigned int*)col->data[i] < *(unsigned int*)value)
                    num_val_s++;
            }
            break;

        case INT:
            for(int i = 0; i < col->lSize; i++)
            {
                if (*(int*)col->data[i] < *(int*)value)
                    num_val_s++;
            }
            break;

            // Smaller in ASCII order
        case CHAR:
            for(int i = 0; i < col->lSize; i++)
            {
                if (*(char*)col->data[i] < *(char*)value)
                    num_val_s++;
            }
            break;

        case FLOAT:
            for(int i = 0; i < col->lSize; i++)
            {
                if (*(float*)col->data[i] < *(float*)value)
                    num_val_s++;
            }
            break;

        case DOUBLE:
            for(int i = 0; i < col->lSize; i++)
            {
                if (*(double*)col->data[i] < *(double*)value)
                    num_val_s++;
            }
            break;

            // Smaller in ASCII order
        case STRING:
            for(int i = 0; i < col->lSize; i++)
            {
                if (strcmp((char*)col->data[i], (char*)value) < 0)
                    num_val_s++;
            }
            break;

            // Smaller in vector's length
        case VEC:
            for (int i = 0; i < col->lSize; i++)
            {
                if (vec_magnitude_comparison((VECTOR*)col->data[i], (VECTOR*)value) < 0)
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
                if ((*(unsigned int *)col->data[i]) == (*(unsigned int *)value))
                    num_val_e++;
            }
            break;

        case INT:
            for(int i = 0; i != (col->lSize); i++)
            {
                if ((*(int *)col->data[i]) == (*(int *)value))
                    num_val_e++;
            }
            break;

            // smaller in alphabetical order
        case CHAR:
            for(int i = 0; i != (col->lSize); i++)
            {
                if ((*(char *)col->data[i]) == (*(char *)value))
                    num_val_e++;
            }
            break;

        case FLOAT:
            for(int i = 0; i != (col->lSize); i++)
            {
                if ((*(float *)col->data[i]) == (*(float *)value))
                    num_val_e++;
            }
            break;

        case DOUBLE:
            for(int i = 0; i != (col->lSize); i++)
            {
                if ((*(double *)col->data[i]) == (*(double *)value))
                    num_val_e++;
            }
            break;

            // smaller in alphabetical order
        case STRING:
            for(int i = 0; i != (col->lSize); i++)
            {
                if (strcmp((char *)col->data[i], (char *)value) == 0)
                    num_val_e++;
            }
            break;

        case VEC:
            for (int i = 0; i < col->lSize; i++) {
                if (vec_comparison((VECTOR*)col->data[i], (VECTOR*)value) == 0) {
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
        sort(col, col->sortDir); // col->sortDir to determine the order
    }
    else if (col->validIndex == -1)
    {
        // Apply insertion sort if the column is partially sorted
        if (col->sortDir == -1)
        {
            insertion_sort(col, DESC);
            col->validIndex = 1; // Mark the index as valid

        }
        else
        {
            insertion_sort(col, ASC);
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
    int high = col->lSize - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int comparison = compare(col->data[mid], val, col->type);

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

#endif