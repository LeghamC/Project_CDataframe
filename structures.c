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

int InsertValue(COLUMN *col, void *value){
    int insertion = 0;
// check memory space
    if (col->lSize >= col->pSize)
    {
        col->data = realloc(col->data, col->pSize + REALLOC_SIZE)
    }
    switch(col->column_type){
        ...
        case INT:
            col->data[col->size] = (int*) malloc (sizeof(int));
            *((int*)col->data[col->size])= *((int*)value);
            break;
            ...
    }
    ...
    col->size++;
    ...
}


/**
 * @brief Deletes the columns and frees its allocated memory
 * @param1 A pointer to the column to delete
 */
void DeleteColumn(COLUMN* column)
{
    free(column->title);
    for (int i = 0; i < column->lSize; i ++) free(column->data[i]);
    free(column->data);
    free(column->index);
    free(column);
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