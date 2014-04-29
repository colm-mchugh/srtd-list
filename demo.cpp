#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strcmp_wrapper(void *s1, void *s2) {
    return strcmp((const char*)s1, (const char*)s2);
}

void gen_random_string(char *buffer, size_t len) {
    static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; i++) {
        buffer[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    buffer[len] = '\0';
}

void demo1(int numstrings, char **strings) {
    List *list = createList();
    for (int i = 0; i < numstrings; i++) {
        appendTo(list, strings[i]);
    }

    for (int i = 0; i < list->num_nodes; i++) {
        printf(" %s ", getElement(list, i));
    }
    printf("\n");

    mergeSort(list, strcmp_wrapper);
    
    for (int i = 0; i < list->num_nodes; i++) {
        printf(" %s ", getElement(list, i));
    }
    printf("\n");
}

void demo2(int numstrings, char **strings) {
    List *list = createList();
    for (int i = 0; i < numstrings; i++) {
        addInSortedOrder(list, strings[i], strcmp_wrapper);
    }
    for (int i = 0; i < list->num_nodes; i++) {
        printf(" %s ", getElement(list, i));
    }
    printf("\n");
}


int main(int argc, char **argv) {
    demo1(argc, argv);
    demo2(argc, argv);
}
