#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("COPY TEST: ");

    ListInt list = {0};
    ListInt list_copy = {0};

    ll_copy(list_copy, list, NodeInt);

    assert(list.first == list_copy.first);  assert(list_copy.first == NULL);
    assert(list.last == list_copy.last);    assert(list_copy.last == NULL);
    assert(list.count == list_copy.count);  assert(list_copy.count == 0);

    for (int i=0; i<12; i++) {
        ll_append_back(list, NodeInt, i*i);
    }

    ll_copy(list_copy, list, NodeInt);
    assert(list.count == list_copy.count);
    NodeInt* it1 = list.first;
    NodeInt* it2 = list_copy.first;
    int i = 0;
    while (i < list.count) {
        assert(it1->item == it2->item);

        it1 = it1->next;
        it2 = it2->next;
        i++;
    }

    ll_free(list);
    ll_free(list_copy);
    assert(free_calls == malloc_calls);

    printf("OK\n");
    return 0;
}