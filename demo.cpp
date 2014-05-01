#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

// The data in our lists will be char* strings, so 
// create a comparator function that can be used by the List api:
int strcmp_wrapper(void *s1, void *s2) {
    return strcmp((const char*)s1, (const char*)s2);
}

// Cleanup function used to free data by List api
bool cleanup(void *data) {
    free(data);
    return true;
}

// Put a randomly generated string in the given buffer
// (Caller's responsibility to ensure buffer has sufficient memory)
void gen_random_string(char *buffer, size_t len) {
    static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; i++) {
        buffer[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    buffer[len] = '\0';
}

// Create and return an array of numstrings character strings
char **make_random_string_array(size_t numstrings, size_t numchars) {
    char **strings = (char**)malloc((numstrings + 1)*sizeof(char*));
    for (int i = 0; i < numstrings; i++) {
        // The length of the string is randomly generated:
        size_t string_len = rand() % (numchars + 1);
        // Allocate memory for the characters and trailing nul character:
        strings[i] = (char*)malloc((string_len + 1)* sizeof(char));
        // Use gen_random_string to generate the content:
        gen_random_string(strings[i], string_len);
    }
    // Add NULL endmarker
    strings[numstrings] = NULL;
    return strings;
}

// Append all the given character strings to a list, and merge sort the list.
// Given the same input, appendAndSort will produce the same output as addSorted.
List *appendAndSort(char **strings) {
    List *list = createList();
    for (int i = 0; strings[i] != NULL; i++) {
        appendTo(list, strings[i]);
    }
    mergeSort(list, strcmp_wrapper);
    return list;
}

// Add all the given character strings to a list in sorted order.
// Given the same input, addSorted will produce the same output as appendAndSort.
List *addSorted(char **strings) {
    List *list = createList();
    for (int i = 0; strings[i] != NULL; i++) {
        addInSortedOrder(list, strings[i], strcmp_wrapper);
    }
    return list;
}

// Basic timing test rig: set up an array of words, add the words to a list using the given function,
// and measure how long it takes to populate the list. 
void time_it( List* (*populate_list)(char**), size_t ns, size_t sz, const char *description ) {
    struct timeval stop, start;
    char **words = make_random_string_array(ns, sz);
    gettimeofday(&start, NULL);
    List *list = populate_list(words);
    gettimeofday(&stop, NULL);
    printf("%s %d nodes: %lu usecs (%lu seconds)\n", description, list_size(list), stop.tv_usec - start.tv_usec, stop.tv_sec - start.tv_sec);
    if (!isSorted(list, strcmp_wrapper)) {
        printf("WARNING: list is not sorted\n");
    }
    deleteList(&list, cleanup);
    free(words);
}

// Invoke the list populator functions (appendAndSort, addSorted) with different sizes of word sets
int main(int argc, char **argv) {
    size_t ns[] = { 16, 64, 256, 1024, 4096, 8192, 16384, 32768, 65536, -1 } ;
    size_t sz = 16;

    for (int i = 0; ns[i] != -1; i++) {
        time_it(appendAndSort, ns[i], sz, "Append followed by mergesort");
        time_it(addSorted, ns[i], sz, "Adding in sorted order");
        printf("\n");
    }
    return 1;
}
