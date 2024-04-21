#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "column.h"

/**
 * @brief: Creates an empty column with the given title
 * @param1: The type of the values of the column
 * @param2: The title of the column
 * @return: A pointer to the new column
 */
COLUMN* create_column(ENUM_TYPE type, char* title)
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

        case STRUCTURE:
        {
            // Allocation for structured type values
            (col->data)[col->lSize] = malloc(sizeof(value));
            if ((col->data)[col->lSize] == NULL) return 0;

            // We only store a pointer to the object.
            (col->data)[col->lSize] = value;
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
void delete_column(COLUMN **col)
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
void convert_value(COLUMN* column, unsigned long long index, char* str, int size)
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