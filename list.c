/** ---------------------------------------------------------------------------------------
# Name:        CDataframe
# Author:      BABOULAT Léandre - GHEZALI Lélia
# Purpose:     Project's list's file - implement functions and operations to
               manage and manipulate the double-linked list used for the dataframe
-----------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "list.h"

NODE* node_create(COLUMN* col, NODE* previous, NODE* next)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = col;
    newNode->previous = previous;
    if (previous != NULL) previous->next = newNode;
    newNode->next = next;
    if (next != NULL) next->previous = newNode;
    return newNode;
}

void node_delete(NODE* node)
{
    free(node->data);
    free(node->next);
    free(node->previous);
    free(node);
}

void node_set_value(NODE* node, COLUMN* value)
{
    node->data = value;
}

void node_set_next(NODE* node, NODE* next)
{
    node->next = next;
}

void node_set_previous(NODE* node, NODE* previous)
{
    node->next = previous;
}

LIST* list_create()
{
    LIST* newList = (LIST*)malloc(sizeof(LIST));
    newList->first = NULL;
    newList->last = NULL;
    return newList;
}

void list_delete(LIST* list)
{
    int l = list_length(list);

    for (int i = l - 1; i >= 0; i ++) {
        NODE* lastNode = list_get(list, i);
        node_delete(lastNode);
    }
    free(list->first);
    free(list->last);
    free(list);
}

void list_set_start(LIST* list, NODE* start)
{
    list->first = start;
}

void list_set_end(LIST* list, NODE* end)
{
    list->first = end;
}

int list_length(LIST* list)
{
    if (list->first == NULL) return 0;
    int length = 1;
    NODE* currentNode = list->first;
    while (currentNode->next != NULL) {
        length ++;
        currentNode = currentNode->next;
    }
    return length;
}

NODE* list_get(LIST* list, int index)
{
    NODE* currentNode = list->first;
    for (int i = 0; i < index; i ++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}