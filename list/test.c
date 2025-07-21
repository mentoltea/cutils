#include "list.h"
#include <stdio.h>

typedef struct NodeInt {
    struct NodeInt* prev;
    struct NodeInt* next;
    int item;
} NodeInt;

typedef struct {
    NodeInt* first;
    NodeInt* last;
    size_t count;
} ListInt;

void print_list(ListInt* l) {
    if (l->count == 0) {
        printf("* EMPTY *");
    }
    ll_foreach(NodeInt, ptr, *l) {
        printf ("%d ", ptr->item);
    }
    printf("\n");
}

int main() {
    ListInt list = {0};
    ListInt list2 = {0};
    
    for (int i=0; i<5; i++) {
        ll_append_back(list, NodeInt, i*i);
    }
    ll_append_front(list, NodeInt, -1);
    printf("APPENDED\n");
    
    printf("List1: ");
    print_list(&list);

    printf("List2: ");
    print_list(&list2);

    ll_copy(NodeInt, list2, list);

    
    printf("List1: ");
    print_list(&list);
    
    printf("List2: ");
    print_list(&list2);
    
    ll_reverse(NodeInt, list2);
    printf("List2 (reversed): ");
    print_list(&list2);

    ll_pop(NodeInt, list2, 1);
    ll_pop(NodeInt, list2, 0);
    printf("List2 (removed): ");
    print_list(&list2);

    ll_concat(ListInt, NodeInt, list, list2);

    printf("List1: ");
    print_list(&list);
    
    printf("List2: ");
    print_list(&list2);


    ll_free(list);
    ll_free(list2);
    printf("FREED\n");

    printf("OK\n");
    return 0;
}