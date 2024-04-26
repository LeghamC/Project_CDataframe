#ifndef LIST_H
#define LIST_H

typedef struct node_ {
    void* data;     // Pointer to the element.
    struct node_* previous;
    struct node_* next;
}NODE;

typedef struct {
    NODE* first;
    NODE* last;
}LIST;

NODE* node_create();
void node_delete(NODE* node);
void node_set_value(NODE* node, void* value);
void node_set_next(NODE* node, NODE* next);
void node_set_previous(NODE* node, NODE* previous);

LIST* list_create();
void list_delete(LIST* list);
void list_set_start(LIST* list, NODE* start);
void list_set_end(LIST* list, NODE* end);
NODE* list_get(LIST* list, int index);

#endif