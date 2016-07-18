#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>

using namespace std;

// The data in our lists will be char* strings, so 
// create a comparator function that can be used by the List api:
int comparator(void *s1, void *s2) {
    int i1 = *((int*)s1);
    int i2 = *((int*)s2);
    if (i1 > i2) {
   	return 1;
    }
    if (i1 == i2) {
	return 0;
    }
    return -1;
}

// Cleanup function used to free data by List api
bool cleanup(void *data) {
    free(data);
    return true;
}

List *makeList(char *filename) {
    List *list = createList();
    ifstream file(filename);
    int data;
    while (file >> data) {
	int* datap = new int;
        *datap = data;
	appendTo(list, datap);
    }
    return list;
}

void printList(List *list) {
   for (ListNode *node = list->head; node != NULL; node = node->next) {
	cout << *((int*)node->data) << ' ';
   }
   cout << endl;
}

// Invoke the list populator functions (appendAndSort, addSorted) with different sizes of word sets
int main(int argc, char **argv) {

    if (argc != 2) {
	cout << "Usage: " << argv[0] << "/path/to/file/containing/numbers/to/sort" << endl;
	return 0;
    }

    List *l = makeList(argv[1]);
    mergeSort(l, comparator);
    cout << "Number of inversions=" << numInversions() << endl;
    deleteList(&l, cleanup);
    return 1;
}
