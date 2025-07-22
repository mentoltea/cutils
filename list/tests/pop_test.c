#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("POP TEST: ");

    ListInt list = {0};
    
    for (int i=0; i<10; i++) {
        ll_append_back(list, NodeInt, i);
    }

    for (int i=4; i>=0; i--) {
        ll_pop(list, NodeInt, 2*i + 1)
    }

    assert(list.count == 5);

    int j=0;
    ll_foreach(NodeInt, ptr, list) {
        // printf("%d ", ptr->item);
        assert(ptr->item == 2*j);
        j++;
    }

    ll_free(list);
    assert(free_calls == malloc_calls);

    printf("OK\n");
    return 0;
}