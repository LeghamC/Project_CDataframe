/** -----------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's main's file - Allow use of the programs by coordinating the
               creation, manipulation, and display of dataframes, their columns, and
               the sorting and searching functionalities used for it.
----------------------------------------------------------------------------------------- **/

#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "list.h"
#include "column.h"
typedef LIST CDATAFRAME;

CDATAFRAME* cdf_create(const ENUM_TYPE *cdftype, char** names, int size);
void cdf_delete(CDATAFRAME** cdf);
unsigned int cdf_rows_count(CDATAFRAME* cdf);
unsigned int cdf_columns_count(CDATAFRAME* cdf);
COLUMN* cdf_get_column(CDATAFRAME* cdf, int column);
void cdf_fill_with_user_inputs(CDATAFRAME* cdf);
void cdf_hard_fill(CDATAFRAME* cdf);
void cdf_print(CDATAFRAME* cdf);
void cdf_print_rows_between(CDATAFRAME* cdf, int minRow, int maxRow);
void cdf_print_columns_between(CDATAFRAME* cdf, int minColumn, int maxColumn);
void cdf_print_cr_between(CDATAFRAME* cdf, int minRow, int maxRow, int minColumn, int maxColumn);
void cdf_add_row(CDATAFRAME* cdf, COLUMN_TYPE* values);
int cdf_remove_row(CDATAFRAME* cdf, int index);
void cdf_add_column(CDATAFRAME* cdf, COLUMN* col);
int cdf_remove_column(CDATAFRAME* cdf, int index);
int cdf_rename_column(CDATAFRAME* cdf, int index, char* newName);
int cdf_search(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value);
int cdf_get_number_of_values_equal(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value);
int cdf_get_number_of_values_greater(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value);
int cdf_get_number_of_values_smaller(CDATAFRAME* cdf, ENUM_TYPE type, COLUMN_TYPE* value);
COLUMN_TYPE* cdf_get_value(CDATAFRAME* cdf, int row, int column);
int cdf_replace_value(CDATAFRAME* cdf, int row, int columns, void* newValue);
void cdf_display_column_names(CDATAFRAME* cdf);
COLUMN_TYPE* cdf_get_row(char* line);
void cdf_load_csv(char* fileName);

#endif
