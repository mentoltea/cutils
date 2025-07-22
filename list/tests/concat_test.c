#include "../test_utility.c"
#include "../list.h"

int main() {
    printf("CONCAT TEST: ");

    ListInt list1 = {0};
    ListInt list2 = {0};
    NodeInt *it1, *it2, *it3;
    int i;

    for (int i=0; i<20; i++) {
        if (i < 10) ll_append_back(list1, NodeInt, i)
        else ll_append_back(list2, NodeInt, i)
    }

    ll_concat_raw(list1, list2);

    // printf("List1 (%d items): ", list1.count);
    // ll_foreach(NodeInt, ptr, list1) {
    //     printf("%d ", ptr->item);
    // }
    // printf("\n");
    
    // printf("List2 (%d items): ", list2.count);
    // ll_foreach(NodeInt, ptr, list2) {
    //     printf("%d ", ptr->item);
    // }
    // printf("\n");

    assert(list1.count == list2.count);
    assert(list1.count == 20);
    it1 = list1.first;
    it2 = list2.first;
    i = 0;
    while (i < list1.count) {
        assert(it1 == it2);
        // automatically true from it1 == it2
        // assert(it1->item == it2->item);

        it1 = it1->next;
        it2 = it2->next;
        i++;
    }

    ll_free(list1);
    list2.first = list2.last = NULL;
    list2.count = 0;
    assert(free_calls == malloc_calls);

    for (int i=0; i<20; i++) {
        if (i < 10) ll_append_back(list1, NodeInt, i)
        else ll_append_back(list2, NodeInt, i)
    }

    ListInt list3 = {0};
    ll_copy(list3, list1, NodeInt);

    ll_concat(ListInt, NodeInt, list3, list2);

    assert(list3.count == list1.count + list2.count);
    assert(list3.first != list1.first); assert(list3.last != list1.last);
    assert(list3.first != list2.first); assert(list3.last != list2.last);
    
    it1 = list1.first;
    it2 = list2.first;
    it3 = list3.first;
    i = 0;
    while (i < list1.count) {
        if (i < 10) {
            assert(it3->item == it1->item);
            it1 = it1->next;
        } else {
            assert(it3->item == it2->item);
            it2 = it2->next;
        }

        it3 = it3->next;
        i++;
    }

    ll_free(list1);
    ll_free(list2);
    ll_free(list3);
    assert(free_calls == malloc_calls);

    printf("OK\n");
    return 0;
}