#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("REVERSE TEST: ");

    ListInt list = {0};

    for (int i=0; i<20; i++) {
        if (i%2 == 0) ll_append_front(list, NodeInt, i)
        else ll_append_back(list, NodeInt, i)
    }

    int i=0;
    ll_foreach(NodeInt, ptr, list) {
        // printf("%d ", ptr->item);
        if (i < 10) assert(ptr->item % 2 == 0);
        else assert(ptr->item % 2 == 1);
        i++;
    }
    // printf("\n");
    
    ll_reverse(list, NodeInt);
    i=0;
    ll_foreach(NodeInt, ptr, list) {
        // printf("%d ", ptr->item);
        if (i < 10) assert(ptr->item % 2 == 1);
        else assert(ptr->item % 2 == 0);
        i++;
    }
    // printf("\n");

    ll_free(list);
    assert(free_calls == malloc_calls);

    printf("OK\n");
    return 0;
}