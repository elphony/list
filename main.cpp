#include <stdio.h>
#include <stdlib.h>

typedef int ListElem_t;

struct ElemList {
    ListElem_t value;
    ListElem_t next;
    ListElem_t prev;
};

struct list {
    ElemList* data;
    int size;
    int head;
    int tail;
    int free;
};

void list_ctor(list* my_list, int size) {
    my_list->data = (ElemList*)calloc(size + 1, sizeof(ElemList));
    my_list->size = size;

    for (int i = 1; i < my_list->size; ++i) {
        my_list->data[i].next = i + 1;
    }

    my_list->head = 1;
    my_list->tail = 1;
    my_list->free = 1;
}

void list_dtor(list* my_list) {
    free(my_list->data);
    my_list->size = 0;
    my_list->head = 0;
    my_list->tail = 0;
    my_list->free = 0;
}

void list_insert(list* list, int index, ListElem_t value) {

    int new_index = list->free;
    list->free = list->data[new_index].next;
    list->data[new_index].value = value;

    if (index == list->tail) {
        list->tail = new_index;
        list->data[new_index].next = 0;
    }

    else {
        list->data[new_index].next = list->data[index].next; 
        list->data[list->data[new_index].next].prev = new_index; 
    }

    list->data[index].next = new_index;
    list->data[new_index].prev = index; 
}

void list_dump(list* my_list) {

    fprintf(stderr, "NEW DUMP\n");
    fprintf(stderr, "DATA:\n");
    for (int i = 0; i < my_list->size; ++i) {
        fprintf(stderr, "\t[%d] = %d\n", i, my_list->data[i].value);
    }
    fprintf(stderr, "LIST:\n");
    for (int i = 0; i < my_list->size; ++i) {
        fprintf(stderr, "\t[%d] = %d\n", i, my_list->data[my_list->data[i].next].value);
    }
}

int main() {
    list my_list = {};

    list_ctor(&my_list, 10);
    list_dump(&my_list);
    list_insert(&my_list, 1, 10);
    list_dump(&my_list);
    list_insert(&my_list, 2, 20);
    list_dump(&my_list);
    list_insert(&my_list, 2, 15);
    list_dump(&my_list);
    list_dtor(&my_list);
}