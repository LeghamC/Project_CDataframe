/** -----------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's main's file - Allow use of the programs by coordinating the
               creation, manipulation, and display of dataframes, their columns, and
               the sorting and searching functionalities used for it.
----------------------------------------------------------------------------------------- **/

#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include "list.h"
#include "cdataframe.h"
#include "vector.h"

int main()
{
    ENUM_TYPE colTypes[2] = {STRING, INT};
    char* colNames[2] = {"Name", "ID"};
    CDATAFRAME* cdf = cdf_create(colTypes, colNames, 2);

    // Adding Lélia.
    COLUMN_TYPE* newRow = (COLUMN_TYPE*)malloc(2 * sizeof(COLUMN_TYPE));
    newRow[0].string_value = "Lelia";
    newRow[1].int_value = 12;
    cdf_add_row(cdf, newRow);

#if 1
    COLUMN_TYPE* newRow2 = (COLUMN_TYPE*)malloc(2 * sizeof(COLUMN_TYPE));
    newRow2[0].string_value = "Leandre";
    newRow2[1].int_value = 18;
    cdf_add_row(cdf, newRow2);
#endif

#if 0
    cdf_hard_fill(cdf);
#endif

#if 0
    COLUMN* newCol = col_create(DOUBLE, "Grade");

    COLUMN_TYPE* newCol1 = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    newCol1->double_value = 15.06;
    col_insert_value(newCol, newCol1);

    COLUMN_TYPE* newCol2 = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    newCol2->double_value = 18.23;
    col_insert_value(newCol, newCol2);

    cdf_add_column(cdf, newCol);
#endif

#if 0
    cdf_print_columns_between(cdf, 1, 3);
#endif

#if 0
    cdf_print_rows_between(cdf, 1, 2);
#endif

#if 0
    cdf_rename_column(cdf, 0, "Surname");
#endif

#if 0
    COLUMN_TYPE* searchValue = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    searchValue->int_value = 12;
    printf("Found the value : %d\n", cdf_search(cdf, INT, searchValue));
#endif

#if 0
    COLUMN_TYPE* searchValue = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    searchValue->int_value = 12;
    printf("Number of values equal to : %d\n", cdf_get_number_of_values_equal(cdf, INT, searchValue));
#endif

#if 0
    COLUMN_TYPE* searchValue = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    searchValue->int_value = 12;
    printf("Number of values greater than : %d\n", cdf_get_number_of_values_greater(cdf, INT, searchValue));
#endif

#if 0
    COLUMN_TYPE* getValue = cdf_get_value(cdf, 0, 0);
    printf("%s\n", getValue->string_value);
#endif

#if 0
    COLUMN_TYPE* replaceValue = (COLUMN_TYPE*)malloc(sizeof(COLUMN_TYPE));
    replaceValue->string_value = "Manon";
    cdf_replace_value(cdf, 0, 0, replaceValue);
#endif


    cdf_print(cdf);

    return 0;
}