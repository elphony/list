#ifndef LIST_H
#define LIST_H

typedef int ListElem_t;

const ListElem_t POISON = -666;

struct list {
    ListElem_t* value;
    int* next;
    int* prev;
    int size;
    int free;
};

void list_ctor(list* list, int size);
void list_dtor(list* list);
void list_insert_after(list* list, int index, ListElem_t value);
void list_insert_before(list* list, int index, ListElem_t value);
void list_insert_start(list* list, ListElem_t value);
void list_insert_end(list* list, ListElem_t value);
void list_delete_index(list* list, int index);
void list_dump(list* list);

#endif