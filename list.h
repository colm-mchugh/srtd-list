#ifndef _list_h
#define _list_h

// Double-linked list implementation

typedef struct _node {
	void *data;
	struct _node *next;
	struct _node *prev;
} ListNode;

typedef struct _list {
	ListNode *head;
	ListNode *tail;
	int num_nodes;
} List;

static unsigned long num_inversions = 0;

#define list_size(l) (l->num_nodes)

typedef bool (*equals)(void*, void*);

typedef bool (*deleter)(void*);

typedef int (*compare)(void*, void*);

// Create an empty list
List *createList();

// Delete all nodes in a list, applying deleter function to each node's data
void deleteList(List**, deleter);

// Return the data at the given index (NULL if no such index)
void *getElement(List*, int);

// Return the data that matches the given equals function and data (NULL if no match)
void *getMatch(List *, equals , void *);

// Remove the data at the given index (nop if no such index)
void *removeElement(List*, int);

// Remove the node that contains the given data (nop if not in list)
void *removeIfExists(List*, void*);

// Append the given data at the end of the list
void appendTo(List*, void*);

// Prepend the given data to the start of the list
void prependTo(List*, void*);

// Add the given data to the list in sorted order 
void addInSortedOrder(List*, void*, compare);

// Is the list sorted?
bool isSorted(List*, compare);

// Mergesort the given list
void mergeSort(List*, compare);

// Return number of inversions
unsigned long numInversions();
#endif
