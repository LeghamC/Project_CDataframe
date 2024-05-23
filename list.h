#ifndef LIST_H
#define LIST_H

#include "column.h"

typedef struct node_ {
    COLUMN* data;     // Pointer to the element.
    struct node_* previous;
    struct node_* next;
}NODE;

typedef struct {
    NODE* first;
    NODE* last;
}LIST;

NODE* node_create(COLUMN* col);
void node_delete(NODE* node);
void node_set_value(NODE* node, COLUMN* value);
void node_set_next(NODE* node, NODE* next);
void node_set_previous(NODE* node, NODE* previous);

LIST* list_create();
void list_delete(LIST* list);
void list_set_start(LIST* list, NODE* start);
void list_set_end(LIST* list, NODE* end);
int list_length(LIST* list);
NODE* list_get(LIST* list, int index);

#endif