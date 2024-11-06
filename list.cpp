#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "dump.h"

#define LIST_DUMP(stk) create_dump(list, __FILE__, __LINE__, __FUNCTION__) 


void list_ctor(list* list, int size) {

    if (!list) assert(0 && "Null pointer to list");
    if (size < 0) assert(0 && "Negative size");

    list->value = (ListElem_t*)calloc(size, sizeof(ListElem_t));
    list->prev = (int*)calloc(size + 1, sizeof(int));
    list->next = (int*)calloc(size + 1, sizeof(int));

    // проверка выделенной памяти

    for (int i = 1; i < size; ++i) {
        list->value[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->value[0] = POISON;
    list->next[0] = 0;
    list->prev[0] = 0; 

    list->next[size - 1] = -1;
    list->size = size;
    list->free = 1;

    LIST_DUMP(&list);
}

void list_dtor(list* list) {
    free(list->value);
    free(list->prev);
    free(list->next);
    list->size = 0;
    list->free = 0;
}

void list_insert_after(list* list, int index, ListElem_t value) {

    if (list->free == -1) {
        fprintf(stderr, "list ended\n");
        return;
    }

    int new_index = list->free;
    int old_index = list->next[index];

    list->free = list->next[new_index];
    list->value[new_index] = value;

    list->next[index] = new_index;
    list->next[new_index] = old_index;

    list->prev[new_index] = list->prev[old_index];
    list->prev[old_index] = new_index;

    LIST_DUMP(&list);
}

void list_insert_before(list* list, int index, ListElem_t value) {
    
    list_insert_after(list, list->prev[index], value);
}

void list_insert_start(list* list, ListElem_t value) {

    list_insert_after(list, 0, value);
}

void list_insert_end(list* list, ListElem_t value) {

    list_insert_after(list, list->prev[0], value);
}

void list_delete_index(list* list, int index) {
    
    list->value[index] = POISON;

    int next_index = list->next[index];
    int prev_index = list->prev[index];

    list->next[prev_index] = next_index;
    list->prev[next_index] = prev_index;

    list->next[index] = list->free;
    list->prev[index] = -1;
    list->free = index;

    LIST_DUMP(&list);
}

void list_delete_start(list* list) {

    list_delete_index(list, list->next[0]);
}

void list_delete_end(list* list) {

    list_delete_index(list, list->prev[0]);
}

void list_dump(list* list) {

    fprintf(stderr, "NEW DUMP\n");
    fprintf(stderr, "LIST free = %d\n", list->free);
    fprintf(stderr, "DATA:\t\tNEXT:\t\tPREV:\n");
    for (int i = 0; i < list->size; ++i) {
        fprintf(stderr, "[%d] = %2d\t[%d] = %2d\t[%d] = %2d\n", i, list->value[i], i, list->next[i], i, list->prev[i]);
    }
    fprintf(stderr, "LIST:\n");
    int i = list->next[0];
    while (i != 0) {
        fprintf(stderr, "\t[%d] = %d\n", i, list->value[i]);
        i = list->next[i];
    }
}