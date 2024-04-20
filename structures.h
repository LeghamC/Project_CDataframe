#ifndef STRUCTURES_H
#define STRUCTURES_H

#define REALLOC_SIZE 256
#define STR_LENGTH 50

typedef enum{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
}ENUM_TYPE;

typedef struct{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COLUMN_TYPE;

typedef struct{
    char* title;
    unsigned int pSize; // Physical size.
    unsigned int lSize; // Logical size.
    ENUM_TYPE type;     // Type of the values contained in the column.
    COLUMN_TYPE **data;  // Array of pointers to stored data.
    unsigned long long *index;  // Array of integers ???
}COLUMN;

/**
* @brief: Insert a new value into a column
* @param1: Pointer to the column
* @param2: Pointer to the value to insert
* @return: 1 if the value is correctly inserted 0 otherwise
*/
int insert_value(COLUMN *col, void *value);

/**
* @brief: Free the space allocated by a column
* @param1: Pointer to the column
*/
void delete_column(COLUMN **col);



typedef struct{

}C_DATAFRAME;

#endif