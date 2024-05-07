#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

VECTOR* vec_create(float x, float y, float z)
{
    VECTOR* newVec = (VECTOR*)malloc(sizeof(VECTOR));
    newVec->x = x;
    newVec->y = y;
    newVec->z = z;
    return newVec;
}

void vec_destroy(VECTOR* v)
{
    free(v);
}

VECTOR* vec_copy(VECTOR* v)
{
    VECTOR* result = vec_create(v->x, v->y, v->z);
    return result;
}

void vec_print(VECTOR* v)
{
    printf("(%f ; %f ; %f)", v->x, v->y, v->z);
}

void vec_fill(VECTOR* v)
{
    float newVal;
    printf("Enter value of x : ");
    scanf("%f", &newVal);
    v->x = newVal;
    printf("\n");

    printf("Enter value of y : ");
    scanf("%f", &newVal);
    v->y = newVal;
    printf("\n");

    printf("Enter value of y : ");
    scanf("%f", &newVal);
    v->z = newVal;
    printf("\n");
}

void vec_set(VECTOR* v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void vec_minus(VECTOR* v)
{
    v->x *= -1;
    v->y *= -1;
    v->z *= -1;
}

VECTOR* mat_add(VECTOR* v1, VECTOR* v2)
{
    VECTOR* result = vec_create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
    return result;
}

float vec_dot_product(VECTOR* v1, VECTOR* v2)
{
    float result = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
    return result;
}

VECTOR* vec_cross_product(VECTOR* v1, VECTOR* v2)
{
    float x = v1->y * v2->z - v1->z * v2->y;
    float y = v1->z * v2->x - v1->x * v2->z;
    float z = v1->x * v2->y - v1->y * v2->x;
    return vec_create(x, y, z);
}