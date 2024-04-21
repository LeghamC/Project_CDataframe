#include <stdio.h>
#include <stdlib.h>
#include "column.h"

int main()
{
    COLUMN* col = create_column(STRING, "Test");
    print_col(col);
    char* names[10] = {"Lelia", "Leandre", "Yannis", "Idrissa", "Louis"};

    for (int i = 0; i < 5; i ++) {
        insert_value(col, names[i]);
    }
    print_col(col);

    return 0;
}