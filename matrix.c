#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

MATRIX* mat_create(int sizeX, int sizeY, float** data)
{
    MATRIX* newMat = (MATRIX*)malloc(sizeof(MATRIX));
    newMat->sizeX = sizeX;
    newMat->sizeY = sizeY;
    if (data != NULL) newMat->data = data;
    else {
        for (int i = 0; i < sizeY; i ++) {
            for (int j = 0; j < sizeX; j ++) {
                newMat->data[i][j] = 0;
            }
        }
    }
    return newMat;
}

void mat_destroy(MATRIX* mat)
{
    free(mat->data);
    free(mat);
}

MATRIX* mat_copy(MATRIX* mat)
{
    MATRIX* result = mat_create(mat->sizeX, mat->sizeY, NULL);
    for (int i = 0; i < mat->sizeY; i ++) {
        for (int j = 0; j < mat->sizeX; j ++) {
            result->data[i][j] = mat->data[i][j];
        }
    }
    return result;
}

void mat_print(MATRIX* mat)
{
    for (int i = 0; i < mat->sizeY; i ++) {
        for (int j = 0; j < mat->sizeX; j ++) {
            printf("%f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void mat_fill(MATRIX* mat)
{
    for (int i = 0; i < mat->sizeY; i ++) {
        for (int j = 0; j < mat->sizeX; j ++) {
            float newVal;
            printf("Enter value at (%d;%d) : ", i+1, j+1);
            scanf("%f", &newVal);
            mat->data[i][j] = newVal;
            printf("\n");
        }
    }
}

void mat_set(MATRIX* mat, float** data)
{
    mat->data = data;
}

void mat_minus(MATRIX* mat)
{
    for (int i = 0; i < mat->sizeY; i ++) {
        for (int j = 0; j < mat->sizeX; j++) {
            mat->data[i][j] *= -1;
        }
    }
}

MATRIX* mat_add(MATRIX* m1, MATRIX* m2)
{
    MATRIX* result = mat_create(m1->sizeX, m1->sizeY, NULL);
    for (int i = 0; i < m1->sizeX; i ++) {
        for (int j = 0; j < m1->sizeY; j ++) {
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }
    return result;
}

MATRIX* mat_multiply(MATRIX* m1, MATRIX* m2)
{
    if (m1->sizeX != m2->sizeY) return NULL;

    MATRIX* result = mat_create(m2->sizeX, m1->sizeY, NULL);
    for (int i = 0; i < m1->sizeY; i ++) {
        for (int j = 0; j < m2->sizeX; j ++) {
            float r = 0;
            for (int k = 0; k < m1->sizeX; k++) {
                r += m1->data[i][k] * m2->data[k][j];
            }
            result->data[i][j] = r;
        }
    }
    return result;
}

void mat_divide_row_by(MATRIX* mat, int row, float coeff)
{
    for (int i = 0; i < mat->sizeX; i ++) {
        mat->data[row][i] /= coeff;
    }
}

void mat_remove_row_from_row(MATRIX* mat, int sub, int base, float coeff)
{
    for (int i = 0; i < mat->sizeX; i ++) {
        mat->data[sub][i] -= coeff * mat->data[base][i];
    }
}

int mat_raise_rows(MATRIX* mat, int row)
{
    float* temp = mat->data[row];
    for (int i = row + 1; i < mat->sizeY; i ++) {
        mat->data[i-1] = mat->data[i];
    }
    mat->data[mat->sizeY - 1] = temp;
    return mat->sizeY - row - 1;
}

float mat_determinant(MATRIX* mat)
{
    if (mat->sizeX != mat->sizeY) return 0;

    float det = 1;
    int i = 0;
    MATRIX* rowEchelon = mat_copy(mat);

    while (i < rowEchelon->sizeY) {
        if (rowEchelon->data[i][i] == 0) {
            int onlyZeros = 1;
            for (int j = i + 1; j < rowEchelon->sizeY; j ++) {
                if (rowEchelon->data[j][i] != 0) onlyZeros = 0;
            }
            if (onlyZeros) {
                free(rowEchelon);
                return 0;
            }

            int minusCount = mat_raise_rows(rowEchelon, i);
            if (minusCount % 2 == 1) det *= -1;
            continue;
        }

        det *= rowEchelon->data[i][i];
        mat_divide_row_by(rowEchelon, i, rowEchelon->data[i][i]);

        for (int j = i + 1; j < rowEchelon->sizeY; j ++) {
            mat_remove_row_from_row(rowEchelon, j, i, rowEchelon->data[j][i]);
        }
    }
    free(rowEchelon);
    return det;
}