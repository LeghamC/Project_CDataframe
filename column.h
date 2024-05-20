#ifndef COLUMN_H
#define COLUMN_H

#include "vector.h"

#define REALLOC_SIZE 256
#define STR_LENGTH 30   // + 1 for the '\0' character.
#define ASCENDING 1
#define DESCENDING 0


typedef enum{
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, VEC
}ENUM_TYPE;

typedef struct{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    VECTOR* vector_value;
}COLUMN_TYPE;

typedef struct{
    char* title;
    ENUM_TYPE type;     // Type of the values contained in the column.
    COLUMN_TYPE **data;  // Array of pointers to stored data.
    unsigned int pSize; // Physical size.
    unsigned int lSize; // Logical size.
    unsigned long long *index;  // Array of integers ???
    int validIndex;     // 0 = no index, 1 = valid index, -1 = invalid index.
    int sortDir;    // 0 = not sorted, 1 = ascending order, -1 = descending order.
}COLUMN;

COLUMN* col_create(ENUM_TYPE type, char* title);
int col_insert_value(COLUMN *col, void *value);
void col_delete(COLUMN **col);
void col_convert_value(COLUMN* col, unsigned int index, char* str, int size);
void col_print(COLUMN *col);
int col_occurrences(COLUMN* col, void* value);
void* col_get_value_at(COLUMN* col, int index);
int col_get_number_of_values_greater(COLUMN* col, void* value);
int col_get_number_of_values_smaller(COLUMN* col, void* value);
int col_get_number_of_values_equal(COLUMN* col, void* value);
void col_print_by_index(COLUMN *col);
void col_erase_index(COLUMN *col);
int col_check_index(COLUMN *col);
void col_update_index(COLUMN* col);
int col_search_value(COLUMN* col, void* value);

typedef struct{

}C_DATAFRAME;

#endif