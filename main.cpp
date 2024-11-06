#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "dump.h"

int main() {
    list list = {};

    list_ctor(&list, 9);
    
    list_insert_after(&list, 0, 10);
    list_insert_after(&list, 1, 20);
    list_insert_after(&list, 1, 15);
    list_insert_start(&list, 5);
    list_delete_index(&list, 1);

    create_html(&list);

    list_dtor(&list);
}