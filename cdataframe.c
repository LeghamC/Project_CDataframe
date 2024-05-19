#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "cdataframe.h"
#include "column.h"
#include "vector.h"

CDATAFRAME* cdf_create(ENUM_TYPE *cdftype, char** names, int size)
{
    CDATAFRAME* newCdf = (CDATAFRAME*)list_create();
    NODE* currentNode = newCdf->first;
    for (int i = 0; i < size; i ++) {
        COLUMN* newColumn = col_create(*(cdftype+i), *(names+i));
        currentNode = node_create(newColumn, currentNode, NULL);
        currentNode = currentNode->next;
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
    if (cdf->first == NULL || cdf->first->data->data == NULL) return 0;
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
                    scanf("%ld", (long*)(curCol->data)[i]); break;
                case INT:;
                    scanf("%d", (int*)(curCol->data)[i]); break;
                case CHAR:;
                    scanf("%c", (char*)(curCol->data)[i]); break;
                case FLOAT:;
                    scanf("%f", (float*)(curCol->data)[i]); break;
                case DOUBLE:;
                    scanf("%lf", (double*)(curCol->data)[i]); break;
                case STRING:;
                    fgets((char*)(curCol->data)[i], STR_LENGTH, stdin); break;
                case VEC:;      // NE PAS ENLEVER CE ; JSP PK FAUT LE METTRE MAIS SANS CA MARCHE PAS
                    VECTOR* newVec = vec_create(0, 0, 0);
                    vec_fill(newVec);
                    curCol->data[i] = newVec;
                    break;
                default:;
                    scanf("%ld", (long*)(curCol->data)[i]); break;
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
                    unsigned int uint = 0;
                    curCol->data[i] = &uint; break;
                case INT:;
                    int integer = 0;
                    curCol->data[i] = &integer; break;
                case CHAR:;
                    char character = 0;
                    curCol->data[i] = &character; break;
                case FLOAT:;
                    float floating = 0;
                    curCol->data[i] = &floating; break;
                case DOUBLE:;
                    double doubleFloat = 0;
                    curCol->data[i] = &doubleFloat; break;
                case STRING:;
                    char* str = "abc";
                    curCol->data[i] = &str; break;
                case VEC:;
                    curCol->data[i] = vec_create(0, 0, 0); break;
                default:
                    scanf("%ld", (long*)(curCol->data)[i]); break;
            }
        }
    }
}

void cdf_print_header(CDATAFRAME* cdf)
{
    // Header.
    printf("     |");
    for (int j = 0; j < cdf_columns_count(cdf); j++) {
        COLUMN *curCol = cdf_get_column(cdf, j);
        printf(" %*s%s%*s |", (STR_LENGTH - strlen(curCol->title)) / 2, curCol->title,
               (STR_LENGTH - strlen(curCol->title)) / 2);
    }
    printf("\n");
}

void cdf_print(CDATAFRAME* cdf) {
    unsigned int colCount = cdf_columns_count(cdf);
    cdf_print_header(cdf);

    // Core.
    for (int i = 0; i < cdf_rows_count(cdf); i++) {
        printf("%d%*s |", i + 1, 4 - (int) ((ceil(log10(i + 1)) + 1)));
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, STR_LENGTH - strlen(currentBuffer));
        }
    }
}

void cdf_print_rows_between(CDATAFRAME* cdf, int minRow, int maxRow)
{
    unsigned int colCount = cdf_columns_count(cdf);
    cdf_print_header(cdf);

    // Core.
    for (int i = minRow; i < maxRow; i++) {
        printf("%d%*s |", i + 1, 4 - (int) ((ceil(log10(i + 1)) + 1)));
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, STR_LENGTH - strlen(currentBuffer));
        }
    }
}

void cdf_print_columns_between(CDATAFRAME* cdf, int minColumn, int maxColumn)
{
    unsigned int colCount = cdf_columns_count(cdf);

    // Header.
    printf("     |");
    for (int j = minColumn; j < maxColumn; j++) {
        COLUMN *curCol = cdf_get_column(cdf, j);
        printf(" %*s%s%*s |", (STR_LENGTH - strlen(curCol->title)) / 2, curCol->title,
               (STR_LENGTH - strlen(curCol->title)) / 2);
    }
    printf("\n");

    // Core.
    for (int i = minColumn; i < maxColumn; i++) {
        printf("%d%*s |", i + 1, 4 - (int) ((ceil(log10(i + 1)) + 1)));
        for (int j = 0; j < colCount; j++) {
            char currentBuffer[STR_LENGTH];
            col_convert_value(cdf_get_column(cdf, j), i, currentBuffer, STR_LENGTH);
            printf(" %s%*s |", currentBuffer, STR_LENGTH - strlen(currentBuffer));
        }
    }
}