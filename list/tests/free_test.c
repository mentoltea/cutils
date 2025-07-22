#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("FREE TEST: ");

    ListInt list = {0};
    
    ll_free(list);
    assert(free_calls == 0);
    assert(free_calls == malloc_calls);
    
    list.first = list.last = test_malloc(sizeof(NodeInt));
    list.first->prev = list.first->next = NULL;
    
    ll_free(list);
    assert(free_calls == 1);
    assert(free_calls == malloc_calls);
    assert(list.first == NULL);
    assert(list.last == NULL);
    assert(list.count == 0);
    
    list.first = test_malloc(sizeof(NodeInt));
    list.first->prev = NULL;

    list.first->next = test_malloc(sizeof(NodeInt));
    list.first->next->prev = list.first;
    
    list.last = test_malloc(sizeof(NodeInt));
    list.last->next = NULL;
    list.last->prev = list.first->next;
    list.first->next->next = list.last;
    
    ll_free(list);
    assert(free_calls == malloc_calls);
    assert(list.first == NULL);
    assert(list.last == NULL);
    assert(list.count == 0);

    printf("OK\n");
    return 0;
}