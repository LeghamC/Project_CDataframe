/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's main's file - Allow use of the programs by coordinating the
               creation, manipulation, and display of dataframes, their columns, and
               the sorting and searching functionalities used for it.
-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include "list.h"
#include "cdataframe.h"
#include "vector.h"

int main()
{
    /* In this example, we create a "class" CDATAFRAME containing, for each student, its first and last name, its average
     * and its last value. Only 5 test students are implemented here (the rest will be done once we can load a CSV file). */

    COLUMN* newCol = col_create(DOUBLE, "Hello");
    double test1 = 3.1415, test2 = 2.7182, test3 = 3.1415, test4 = 0.2305;
    int test = col_insert_value(newCol, &test1);
    col_insert_value(newCol, &test2);
    col_insert_value(newCol, &test3);
    col_insert_value(newCol, &test4);
    col_print(newCol);
    //printf("%c\n", col_get_value_at(newCol, 0)->char_value);
    printf("%d\n", col_get_number_of_values_equal(newCol, &test2));
    printf("%d\n", col_get_number_of_values_greater(newCol, &test2));
    printf("%d\n", col_get_number_of_values_smaller(newCol, &test2));

    col_sort(newCol, ASC);
    col_print_by_index(newCol);

    return 0;

#if 0
    // Create the "class" CDATAFRAME.
    ENUM_TYPE cdftype[] = {STRING, STRING, FLOAT, INT};
    CDATAFRAME* class = cdf_create(cdftype, 40);

    // Create each column of the "class".
    COLUMN* fName = col_create(STRING, "First name");
    COLUMN* lName = col_create(STRING, "Last name");
    COLUMN* average = col_create(FLOAT, "Average");
    COLUMN* l = col_create(INT, "???");

    // Putting the columns in the "class" CDATAFRAME.
    cdf_add_column(class, fName);
    cdf_add_column(class, lName);
    cdf_add_column(class, average);
    cdf_add_column(class, l);

    // Adding Lélia.
    col_insert_value(fName, "Lelia");
    col_insert_value(lName, "GHEZALI");
    float curAverage = 15;
    col_insert_value(average, &curAverage);
    int curL = 11;
    col_insert_value(l, &curL);

    // Adding Léandre.
    col_insert_value(fName, "Leandre");
    col_insert_value(lName, "BABOULAT");
    curAverage = 17;
    col_insert_value(average, &curAverage);
    curL = 0;
    col_insert_value(l, &curL);

    // Adding Louis.
    col_insert_value(fName, "Louis");
    col_insert_value(lName, "CHAMPIGNEULLE");
    curAverage = 14;
    col_insert_value(average, &curAverage);
    curL = 6;
    col_insert_value(l, &curL);

    // Adding Idrissa.
    col_insert_value(fName, "Idrissa");
    col_insert_value(lName, "BARRY");
    curAverage = 15;
    col_insert_value(average, &curAverage);
    curL = 7;
    col_insert_value(l, &curL);

    // Adding Antoine.
    col_insert_value(fName, "Antoine");
    col_insert_value(lName, "MROCZKO");
    curAverage = 18;
    col_insert_value(average, &curAverage);
    curL = 8;
    col_insert_value(l, &curL);

    // Displaying the content of "class".
    cdf_print(class);

     return 0;
#endif
}