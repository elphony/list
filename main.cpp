#include <stdio.h>
#include <stdlib.h>

typedef int ListElem_t;

const ListElem_t POISON = -666;

struct list {
    ListElem_t* value;
    int* next;
    int* prev;
    int size;
    int free;
};

void list_ctor(list* list, int size) {

    // проверка указателя и размера

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
        // все массив закончился
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

int main() {
    list list = {};

    list_ctor(&list, 9);
    list_dump(&list);
    
    list_insert_after(&list, 0, 10);
    list_dump(&list);

    list_insert_after(&list, 1, 20);
    list_dump(&list);

    list_insert_after(&list, 1, 15);
    list_dump(&list);

    list_insert_start(&list, 5);
    list_dump(&list);

    list_dtor(&list);
}