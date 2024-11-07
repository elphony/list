#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "dump.h"

const size_t MAX_SIZE_OF_COMMAND = 100;

int count_dump();

void create_dump(list* list, const char* file, int line, const char* func) {

    FILE* dump = fopen("dump/dump.dot", "w");

    fprintf(dump, "digraph list {\n");
    fprintf(dump, "\trankdir = LR\n");

    fprintf(dump, "\theader [shape = Mrecord, style = \"filled\", label = \"list dump from file %s | function %s | line %d\", fillcolor = \"white\", color = \"white\"]", file, func, line);

    fprintf(dump, "\tnode0 [shape = Mrecord, style = \"rounded, filled\", label = \"index: 0 | data: %d | next: %d | prev: %d\", fillcolor = \"grey\"]\n", list->value[0], list->next[0], list->prev[0]);
    for (int i = 1; i < list->size; ++i) {
        fprintf(dump, "\tnode%d [shape = Mrecord, style = \"rounded, filled\", label = \"index: %d | data: %d | next: %d | prev: %d\", fillcolor = \"lightgreen\"]\n", i, i, list->value[i], list->next[i], list->prev[i]);
    }
    fprintf(dump, "\tfree [fillcolor = \"white\", color = \"blue\"]\n");

    int i = list->next[0];
    fprintf(dump, "\tnode0 -> node%d\n", i);

    while (i != 0) {
        fprintf(dump, "\tnode%d -> ", i);
        i = list->next[i];
        fprintf(dump, "node%d\n", i);
    }

    i = list->free;
    fprintf(dump, "\tfree -> node%d\n", i);
    fprintf(dump, "\tnode%d [fillcolor = \"lightblue\"]\n", i);

    while (list->next[i] != -1) {
        fprintf(dump, "\tnode%d [fillcolor = \"lightblue\"]\n", list->next[i]);
        fprintf(dump, "\tnode%d -> ", i);
        i = list->next[i];
        fprintf(dump, "node%d\n", i);
    }

    fprintf(dump, "}\n");
    fclose(dump);
    
    char command[MAX_SIZE_OF_COMMAND] = {};
    sprintf(command, "dot -Tpng dump/dump.dot -o dump/dump%d.png", count_dump());
    system(command);
}

int count_dump() {
    static int num = 0;
    num++;
    return num;
}

void create_html(list* list) {
    int count = count_dump();
    FILE* html_file = fopen("dump/dump.html", "w");
    for (int i = 1; i < count; ++i) {
        fprintf(html_file, "<img src=dump%d.png>\n", i);
    }
    fclose(html_file);
}