#include "list.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

List *createList() {
	List *new_list = (List*)malloc(sizeof(List));
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->num_nodes = 0;
	return new_list;
}

ListNode *createListNode(void *data) {
	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

// free memory allocated for the List
void deleteList(List** list_ptr, deleter delete_fn ) {
	if ((list_ptr != NULL) && (*list_ptr != NULL)) {
		List *list = *list_ptr;
		ListNode *node = list->head;
		ListNode *next_node = NULL;
		while(node != NULL) {
			// save the next node
			next_node = node->next;
			// hand off node's data to deleter function
			if (delete_fn != NULL) {
				delete_fn(node->data);
			}
			free(node);
			node = next_node;
		}
		free(list);
		*list_ptr = NULL;
	}
}

// Add data to the START of the list
void prependTo(List *list, void *data) {
	ListNode *new_node = createListNode(data);
	if (list->head == NULL) {
		list->tail = new_node;
	} else {
		new_node->next = list->head;
		list->head->prev = new_node;
	}
	list->head = new_node;
	list->num_nodes++;
}

// Add data to the END of the list
void appendTo(List *list, void *data) {
	ListNode *new_node = createListNode(data);
	if (list->head == NULL) {
		list->head = new_node;
	} else {
		list->tail->next = new_node;
		new_node->prev = list->tail;
	}
	list->tail = new_node;
	list->num_nodes++;
}

// get element at index (0-indexed)
void *getElement(List *list, int index) {
	if (index >= list->num_nodes) {
		return NULL;
	}
	int i = 0;
	ListNode *n = list->head;
	while (i++ < index) {
		n = n->next;
	}
	return n->data;
}

// get first element matching comp_op
void *getMatch(List *list, compare comp_op, void *data) {
	int i = 0;
	ListNode *n = list->head;
	while ((n != NULL) && !comp_op(n->data, data) ) {
		n = n->next;
	}
	return (n != NULL? n->data : NULL);
}

void *unlinkElement(List *list, ListNode *element);

// Remove first node that contains the given data 
void *removeIfExists(List* list, void* data) {
	ListNode *element = list->head;
	while ((element != NULL) && (element->data != data)) {
		element = element->next;
	}
	if (element != NULL) {
		data = unlinkElement(list, element);
	}
	return data;
}

// remove element at index (0-indexed)
void *removeElement(List *list, int index) {
	void *data = NULL;
	if (index >= list->num_nodes) {
		return data;
	}
	ListNode *element = NULL;
	int i = 0;
	element = list->head;
	while (i++ < index) {
		element = element->next;
	}
	data = unlinkElement(list, element);
	return data;
}

// remove the given ListNode from the list
void *unlinkElement(List *list, ListNode *element) {
	if (element->prev == NULL) {
		list->head = element->next;
	} else {
		element->prev->next = element->next;
	}
	if (element->next == NULL) {
		list->tail = element->prev;
	} else {
		element->next->prev = element->prev;
	}
	void *data = element->data;
	free(element);
	list->num_nodes--;
	return data;
}
		
// Add the given data just before the first node with data greater than it,
// according to the given compare function
void addInSortedOrder(List* list, void *data, compare comp_op) {
    if ((list->head == NULL) || (comp_op(data, list->head->data) < 0)) {
        prependTo(list, data);
        return;
    }
    if (comp_op(list->tail->data, data) < 0) {
        appendTo(list, data);
        return;
    }
    ListNode *tmp = list->head->next;
    while (comp_op(tmp->data, data) < 0) {
        tmp = tmp->next;
    }
	ListNode *new_node = createListNode(data);
    new_node->next = tmp;
    new_node->prev = tmp->prev;
    new_node->prev->next = new_node;
    tmp->prev = new_node;
    list->num_nodes++;
}

bool isSorted(List *list, compare comp_op) {
    bool result = true;
    if (list_size(list) > 1) {
        for(ListNode *node = list->head; node->next != NULL && result; node = node->next) {
            if (comp_op(node->data, node->next->data) > 0) {
                result = false;
            }
        }
    }
    return result;
}

ListNode *mergeSortNodes(ListNode*, compare);

// merge sort the given List
void mergeSort(List *list, compare comp_op) {
    num_inversions = 0;
    ListNode *sorted_nodes = mergeSortNodes(list->head, comp_op);
    list-> head = sorted_nodes;
    list->tail = NULL;
}

unsigned long numInversions() {
    return num_inversions;
}

unsigned long listSize(ListNode *l); 

ListNode * mergeSortNodes(ListNode *list, compare comp_op) {
    if (list == NULL || list->next == NULL) {
        return list;
    }

    ListNode *right = list, *tmp = list, *last = list, *result = NULL, *next = NULL, *tail = NULL;

    // Find middle point of the list
    while (tmp && tmp->next) {
        last = right;
        right = right->next;
        tmp = tmp->next->next;
    }

    // Divide the list (repaired during merges)
    last->next = NULL;

    // Recurse on smaller lists:
    list = mergeSortNodes(list, comp_op);
    right = mergeSortNodes(right, comp_op);

    // list and right are two sorted lists; merge them into one
    while (list || right) {
        if (!right) { // no more right list, take rest of list
            next = list;
            list = list->next;
        } else {
            if (!list) { // no more list, take rest of right
                next = right;
                right = right->next;
            } else { // take smaller of list or right
                if (comp_op(list->data, right->data) <= 0) {
                    next = list;
                    list = list->next;
                } else {
                    next = right;
		    num_inversions += listSize(list);
                    right = right->next;
                }
           }
        }
        if (!result) {
            result = next;
        } else {
            tail->next = next;
        }
        next->prev = tail;
        tail = next;
    }
    return result;
}

unsigned long listSize(ListNode *l) {
    unsigned long rv = 0;
    while (l) {
        rv++;
        l = l->next;
    }
    return rv;
}
