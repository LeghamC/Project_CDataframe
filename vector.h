#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_SIZE 3

typedef struct {
    float x;
    float y;
    float z;
}VECTOR;

VECTOR* vec_create(float x, float y, float z);
void vec_destroy(VECTOR* v);
void vec_print(VECTOR* v);
void vec_fill(VECTOR* v);
void vec_set(VECTOR* v, float x, float y, float z);
void vec_minus(VECTOR* v);
VECTOR* vec_add(VECTOR* v1, VECTOR* v2);
float vec_dot_product(VECTOR* v1, VECTOR* v2);
VECTOR* vec_cross_product(VECTOR* v1, VECTOR* v2);

#endif