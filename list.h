#ifndef LIST_H
#define LIST_H

typedef struct {
    void* data;     // Pointer to the element.
    struct NODE* previous;
    struct NODE* next;
}NODE;

typedef struct {
    NODE* first;
    NODE* last;
}LIST;

#endif