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
    char* colNames[2] = {"Jsp1", "Valeur"};
    CDATAFRAME* cdf = cdf_create(colTypes, colNames, 2);

    COLUMN_TYPE* newRow = (COLUMN_TYPE*)malloc(2 * sizeof(COLUMN_TYPE));
    newRow[0].string_value = "Casino";
    newRow[1].int_value = 5;
    cdf_add_row(cdf, newRow);

    COLUMN_TYPE* newRow2 = (COLUMN_TYPE*)malloc(2 * sizeof(COLUMN_TYPE));
    newRow2[0].string_value = "Fuck";
    newRow2[1].int_value = 69;
    cdf_add_row(cdf, newRow2);

    cdf_print(cdf);

    return 0;
}