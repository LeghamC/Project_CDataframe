#ifndef STRUCTURES_H
#define STRUCTURES_H

#define REALLOC_SIZE 256
#define STR_LENGTH 50   // + 1 for the '\0' character.

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
    ENUM_TYPE type;     // Type of the values contained in the column.
    COLUMN_TYPE **data;  // Array of pointers to stored data.
    unsigned int pSize; // Physical size.
    unsigned int lSize; // Logical size.
    unsigned long long *index;  // Array of integers ???
}COLUMN;

COLUMN* create_column(ENUM_TYPE type, char* title);
int insert_value(COLUMN *col, void *value);
void delete_column(COLUMN **col);



typedef struct{

}C_DATAFRAME;

#endif