/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's dataframe - implement functions and operations to manage,
               manipulate, and analyze data within a DataFrame structure.
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "cdataframe.h"
#include "column.h"
#include "vector.h"

CDATAFRAME* cdf_create(const ENUM_TYPE *cdftype, char** names, int size)
{
    CDATAFRAME* newCdf = (CDATAFRAME*)list_create();
    NODE* currentNode = NULL;
    for (int i = 0; i < size; i ++) {
        COLUMN* newColumn = col_create(*(cdftype+i), *(names+i));
        NODE* newNode = node_create(newColumn);
        if (i == 0) list_set_start(newCdf, newNode);        // THIS DOES NOT WORK.
        else {
            node_set_previous(newNode, currentNode);
            node_set_next(currentNode, newNode);
        }
        list_set_end((LIST*)newCdf, newNode);
        currentNode = newNode;
    }
    return newCdf;
}

void cdf_delete(CDATAFRAME** cdf)
{
    list_delete(*cdf);
    free(cdf);
}

COLUMN* cdf_get_column(CDATAFRAME* cdf, int column)
{
    NODE* node = list_get(cdf, column);
    COLUMN* result = node->data;
    return result;
}

unsigned int cdf_rows_count(CDATAFRAME* cdf)
{
    if (cdf->first == NULL) return 0;
    return cdf->first->data->lSize;
}

unsigned int cdf_columns_count(CDATAFRAME* cdf)
{
    if (cdf->first == NULL) return 0;
    return list_length(cdf);
}

void cdf_fill_with_user_inputs(CDATAFRAME* cdf)
{
    unsigned int colCount = cdf_columns_count(cdf);
    for (int i = 0; i < cdf_rows_count(cdf); i ++) {
        for (int j = 0; j < colCount; j ++) {
            COLUMN* curCol = cdf_get_column(cdf, j);
            printf("%s (%d) : ", curCol->title, i);
            switch (curCol->type) {
                case UINT:;
                    scanf("%u", &curCol->data[i]->uint_value); break;
                case INT:;
                    scanf("%d", &curCol->data[i]->int_value); break;
                case CHAR:;
                    scanf("%c", &curCol->data[i]->char_value); break;
                case FLOAT:;
                    scanf("%f", &curCol->data[i]->float_value); break;
                case DOUBLE:;
                    scanf("%lf", &curCol->data[i]->double_value); break;
                case STRING:;
                    fgets(curCol->data[i]->string_value, STR_LENGTH, stdin); break;
                case VEC:;      // NE PAS ENLEVER CE ; JSP PK FAUT LE METTRE MAIS SANS CA MARCHE PAS
                    VECTOR* newVec = vec_create(0, 0, 0);
                    vec_fill(newVec);
                    curCol->data[i]->vector_value = newVec;
                    break;
                default:;
                    break;
            }
        }
    }
}

void cdf_hard_fill(CDATAFRAME* cdf)
{
    unsigned int colCount = cdf_columns_count(cdf);
    for (int i = 0; i < cdf_rows_count(cdf); i ++) {
        for (int j = 0; j < colCount; j ++) {
            COLUMN* curCol = cdf_get_column(cdf, j);
            switch (curCol->type) {
                case UINT:;
                    curCol->data[i]->uint_value = 0; break;
                case INT:;
                    curCol->data[i]->int_value = 0; break;
                case CHAR:;
                    curCol->data[i]->char_value = '0'; break;
                case FLOAT:;
                    curCol->data[i]->float_value = 0.0; break;
                case DOUBLE:;
                    curCol->data[i]->double_value = 0.0; break;
                case STRING:;
                    char* str = "abc";
                    curCol->data[i]->string_value = str; break;
                case VEC:;
                    curCol->data[i]->vector_value = vec_create(0, 0, 0); break;
                default:
                    break;
            }
        }
    }
}

void cdf_display_column_names(CDATAFRAME* cdf)
{
    // Header.
    printf("     |");
    for (int j = 0; j < cdf_columns_count(cdf); j++) {
        COLUMN *curCol = cdf_get_column(cdf, j);
        printf(" %*s%s%*s |", (int)((STR_LENGTH - strlen(curCol->title)) / 2), "", curCol->title, (int)((STR_LENGTH - strlen(curCol->title)) / 2), "");
    }
    printf("\n");
}

void cdf_print(CDATAFRAME* cdf) {
    unsigned int colCount = cdf_columns_count(cdf);
    cdf_display_column_names(cdf);

    // Core.
    for (int i = 0; i < cdf_rows_count(cdf); i++) {
        printf("%-4d |", i + 1);
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, (int)(STR_LENGTH - strlen(currentBuffer)), "");
        }
        printf("\n");
    }
}

void cdf_print_rows_between(CDATAFRAME* cdf, int minRow, int maxRow)
{
    unsigned int colCount = cdf_columns_count(cdf);
    cdf_display_column_names(cdf);

    // Core.
    for (int i = minRow; i < maxRow; i++) {
        printf("%-4d |", i + 1);
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, (int)(STR_LENGTH - strlen(currentBuffer)), "");
        }
        printf("\n");
    }
}

void cdf_print_columns_between(CDATAFRAME* cdf, int minColumn, int maxColumn)
{
    unsigned int colCount = cdf_columns_count(cdf);

    // Header.
    printf("     |");
    for (int j = minColumn; j < maxColumn; j++) {
        COLUMN *curCol = cdf_get_column(cdf, j);
        printf(" %*s%s%*s |", (int)((STR_LENGTH - strlen(curCol->title)) / 2), "", curCol->title,
               (int)((STR_LENGTH - strlen(curCol->title)) / 2), "");
    }
    printf("\n");

    // Core.
    for (int i = minColumn; i < maxColumn; i++) {
        printf("%-4d |", i + 1);
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, (int)(STR_LENGTH - strlen(currentBuffer)), "");
        }
        printf("\n");
    }
}

void cdf_print_cr_between(CDATAFRAME* cdf, int minRow, int maxRow, int minColumn, int maxColumn)
{
    unsigned int colCount = cdf_columns_count(cdf);

    // Header.
    printf("     |");
    for (int j = minColumn; j < maxColumn; j++) {
        COLUMN *curCol = cdf_get_column(cdf, j);
        printf(" %*s%s%*s |", (int)((STR_LENGTH - strlen(curCol->title)) / 2), "", curCol->title,
               (int)((STR_LENGTH - strlen(curCol->title)) / 2), "");
    }
    printf("\n");

    // Core.
    for (int i = minColumn; i < maxColumn; i++) {
        printf("%d%*s |", i + 1, 4 - (int)((ceil(log10(i + 1)) + 1)), "");
        for (int j = minRow; j < maxRow; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, (int)(STR_LENGTH - strlen(currentBuffer)), "");
        }
    }
}

void cdf_add_row(CDATAFRAME* cdf, COLUMN_TYPE* values)
{
    for (int i = 0; i < cdf_columns_count(cdf); i ++) {
        COLUMN* currentCol = cdf_get_column(cdf, i);
        col_insert_value(currentCol, &(values[i]));
    }
}

int cdf_remove_row(CDATAFRAME* cdf, int index)
{
    unsigned int rowsCount = cdf_rows_count(cdf);
    if (index >= rowsCount || index < 0) return 0;

    unsigned int colCount = cdf_columns_count(cdf);

    // Removing the values.
    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        free(curCol->data[index]);
    }

    // Raising the rows below.
    for (int j = index + 1; j < rowsCount; j ++) {
        for (int i = 0; i < colCount; i ++) {
            COLUMN* curCol = cdf_get_column(cdf, i);
            curCol->data[j-1] = curCol->data[j];
        }
    }

    // Nullifying the last row.
    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        curCol->lSize--;
        free(curCol->data[curCol->lSize]);
    }

    return 1;
}

void cdf_add_column(CDATAFRAME* cdf, COLUMN* col)
{
    NODE* newNode = node_create(col);
    node_set_next(cdf->last, newNode);
    node_set_previous(newNode, cdf->last);
    list_set_end(cdf, newNode);
}

int cdf_remove_column(CDATAFRAME* cdf, int index)
{
    if (index >= cdf_columns_count(cdf)) return 0;

    NODE* curCol = list_get(cdf, index);
    NODE* previous = curCol->previous;
    NODE* next = curCol->next;
    previous->next = next;
    next->previous = previous;
    return 1;
}

int cdf_rename_column(CDATAFRAME* cdf, int index, char* newName)
{
    unsigned int colCount = cdf_columns_count(cdf);
    if (index >= colCount || index < 0) return 0;

    COLUMN* curCol = cdf_get_column(cdf, index);
    free(curCol->title);
    curCol->title = newName;

    return 1;
}

int cdf_search(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value)
{
    unsigned int colCount = cdf_columns_count(cdf);
    unsigned int rowsCount = cdf_rows_count(cdf);

    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        if (curCol->type != type) continue;

        for (int j = 0; j < rowsCount; j ++) {
            switch (type) {
                case UINT:;
                    if (value->uint_value == (curCol->data[j])->uint_value) return 1; break;
                case INT:;
                    if (value->int_value == (curCol->data[j])->int_value) return 1; break;
                case FLOAT:;
                    if (value->float_value == (curCol->data[j])->float_value) return 1; break;
                case DOUBLE:;
                    if (value->double_value == (curCol->data[j])->double_value) return 1; break;
                case CHAR:;
                    if (value->char_value == (curCol->data[j])->char_value) return 1; break;
                case STRING:;
                    if (!strcmp(value->string_value, (char*)curCol->data[j])) return 1; break;
                case VEC:;
                    if (!vec_comparison(value->vector_value, (VECTOR*)curCol->data[j])) return 1; break;
                default:;
                    break;
            }
        }
    }

    return 0;
}

int cdf_get_number_of_values_equal(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value)
{
    unsigned int colCount = cdf_columns_count(cdf);
    unsigned int rowsCount = cdf_rows_count(cdf);
    int count = 0;

    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        if (curCol->type != type) continue;

        for (int j = 0; j < rowsCount; j ++) {
            switch (type) {
                case UINT:;
                    if (value->uint_value == (curCol->data[j])->uint_value) count++; break;
                case INT:;
                    if (value->int_value == (curCol->data[j])->int_value) count++; break;
                case FLOAT:;
                    if (value->float_value == (curCol->data[j])->float_value) count++; break;
                case DOUBLE:;
                    if (value->double_value == (curCol->data[j])->double_value) count++; break;
                case CHAR:;
                    if (value->char_value == (curCol->data[j])->char_value) count++; break;
                case STRING:;
                    if (!strcmp(value->string_value, (char*)curCol->data[j])) count++; break;
                case VEC:;
                    if (!vec_comparison(value->vector_value, (VECTOR*)curCol->data[j])) count++; break;
                default:;
                    break;
            }
        }
    }

    return count;
}

int cdf_get_number_of_values_greater(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value)
{
    unsigned int colCount = cdf_columns_count(cdf);
    unsigned int rowsCount = cdf_rows_count(cdf);
    int count = 0;

    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        if (curCol->type != type) continue;

        for (int j = 0; j < rowsCount; j ++) {
            switch (type) {
                case UINT:;
                    if (value->uint_value > (curCol->data[j])->uint_value) count++; break;
                case INT:;
                    if (value->int_value > (curCol->data[j])->int_value) count++; break;
                case FLOAT:;
                    if (value->float_value > (curCol->data[j])->float_value) count++; break;
                case DOUBLE:;
                    if (value->double_value > (curCol->data[j])->double_value) count++; break;
                case CHAR:;
                    if (value->char_value > (curCol->data[j])->char_value) count++; break;
                case STRING:;
                    if (strcmp(value->string_value, (char*)curCol->data[j]) < 0) count++; break;
                case VEC:;
                    if (vec_magnitude_comparison(value->vector_value, (VECTOR*)curCol->data[j]) < 0) count++; break;
                default:;
                    break;
            }
        }
    }

    return count;
}

int cdf_get_number_of_values_smaller(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value)
{
    unsigned int colCount = cdf_columns_count(cdf);
    unsigned int rowsCount = cdf_rows_count(cdf);
    int count = 0;

    for (int i = 0; i < colCount; i ++) {
        COLUMN* curCol = cdf_get_column(cdf, i);
        if (curCol->type != type) continue;

        for (int j = 0; j < rowsCount; j ++) {
            switch (type) {
                case UINT:;
                    if (value->uint_value < (curCol->data[j])->uint_value) count++; break;
                case INT:;
                    if (value->int_value < (curCol->data[j])->int_value) count++; break;
                case FLOAT:;
                    if (value->float_value < (curCol->data[j])->float_value) count++; break;
                case DOUBLE:;
                    if (value->double_value < (curCol->data[j])->double_value) count++; break;
                case CHAR:;
                    if (value->char_value < (curCol->data[j])->char_value) count++; break;
                case STRING:;
                    if (strcmp(value->string_value, (char*)curCol->data[j]) > 0) count++; break;
                case VEC:;
                    if (vec_magnitude_comparison(value->vector_value, (VECTOR*)curCol->data[j]) > 0) count++; break;
                default:;
                    break;
            }
        }
    }

    return count;
}

COLUMN_TYPE* cdf_get_value(CDATAFRAME* cdf, int row, int column)
{
    if (row >= cdf_rows_count(cdf) || column >= cdf_columns_count(cdf)) return NULL;
    return cdf_get_column(cdf, column)->data[row];
}

int cdf_replace_value(CDATAFRAME* cdf, int row, int column, void* newValue)
{
    if (row >= cdf_rows_count(cdf) || column >= cdf_columns_count(cdf)) return 0;
    cdf_get_column(cdf, column)->data[row] = newValue;
    return 1;
}

COLUMN_TYPE cdf_convert_string_to_value(char* string)
{

}

char* cdf_get_field(char* line)
{
    char* tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
        return tok;
    }
    return NULL;
}

void cdf_load_csv(char* fileName)
{
    FILE* file = fopen(fileName, "r");

    char line[1024];
    while(fgets(line, 1024, file)) {
        char* temp = strdup(line);
    }
}