#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("APPEND TEST: ");

    ListInt list = {0};

    for (int i=0; i<10; i++) {
        ll_append_back(list, NodeInt, i);
    }
    assert(list.count == 10);
    int j=0;
    ll_foreach(NodeInt, ptr, list) {
        assert(ptr->item == j);
        j++;
    }
    assert(j == 10);
    
    ll_free(list);
    assert(free_calls == malloc_calls);
    
    for (int i=0; i<10; i++) {
        ll_append_front(list, NodeInt, i);
    }
    assert(list.count == 10);
    j = 9;
    ll_foreach(NodeInt, ptr, list) {
        assert(ptr->item == j);
        j--;
    }
    assert(j == -1);

    ll_free(list);
    assert(free_calls == malloc_calls);

    printf("OK\n");
    return 0;
}