#include <stdlib.h>
#include <stdio.h>
#include "structures.h"

/**
 * @brief Creates an empty column with the given title
 * @param1 The type of the values of the column
 * @param2 The title of the column
 * @return A pointer to the new column
 */
COLUMN* CreateColumn(ENUM_TYPE type, char* title)
{
    COLUMN* newCol = (COLUMN*)malloc(sizeof(COLUMN));
    newCol->pSize = 0;
    newCol->lSize = 0;
    newCol->type = type;
    newCol->data = NULL;
    return newCol;
}


/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int insert_value(COLUMN *col, void *value)
{
    int insertion = 0;

    // Check the pointers
    if (col == NULL || value == NULL)
        return insertion;

    // Check if there is a need to resize
    if (col->lSize >= col->pSize)
    {
        // Double the previous physical size
        int new_pSize = col->pSize * 2;
        void **newData = realloc(col->data, new_pSize * sizeof(void *));
        if (newData == NULL)
            return insertion;

        col->data = newData;
        col->pSize = new_pSize;
    }

    // Insert the values by column's type
    switch (col->type)
    {
        case INT:
        {
            // Allocate memory for the new integer value
            col->data[col->lSize] = malloc(sizeof(int));
            if (col->data[col->lSize] == NULL)
                return insertion;
            // Copy the integer value into the allocated memory
            *((int *) col->data[col->lSize]) = *((int *) value);
            break;
        }

        case FLOAT:
        {
            // Allocate memory for the new float value
            col->data[col->lSize] = malloc(sizeof(float));
            if (col->data[col->lSize] == NULL)
                return insertion;
            // Copy the float value into the allocated memory
            *((float *) col->data[col->lSize]) = *((float *) value);
            break;
        }

        case DOUBLE:
        {
            // Allocate memory for the new double value
            col->data[col->lSize] = malloc(sizeof(double));
            if (col->data[col->lSize] == NULL)
                return insertion;
            // Copy the double value into the allocated memory
            *((double *) col->data[col->lSize]) = *((double *) value);
            break;
        }

        case LONG:
        {
            // Allocate memory for the new long value
            col->data[col->lSize] = malloc(sizeof(long));
            if (col->data[col->lSize] == NULL)
                return insertion;
            // Copy the long value into the allocated memory
            *((long *) col->data[col->lSize]) = *((long *) value);
            break;
        }

        case CHAR:
        {
            // Allocate memory for the new character value
            col->data[col->lSize] = malloc(sizeof(char));
            if (col->data[col->lSize] == NULL)
                return insertion;
            // Copy the character value into the allocated memory
            *((char *) col->data[col->lSize]) = *((char *) value);
            break;
        }

        default:
            return insertion;
    }
    col->lSize++;
    insertion = 1;
    return insertion;
}


/**
 * @brief Deletes the columns and frees its allocated memory
 * @param1 A pointer to the column to delete
 */
void delete_column(COLUMN **col)
{
    // Case where there is nothing to delete
    if (col == NULL || *col == NULL)
        return;

    // Free memory for col's attributes
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
void ConvertValue(COLUMN* column, unsigned long long index, char* str, int size)
{
    char result[size];

    switch (column->type) {
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
        case UINT:
            snprintf(result, size, "%ud", *((int*)column->data[size]));
            break;
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
        case INT:
            snprintf(result, size, "%d", *((int*)column->data[size]));
            break;
    }
}