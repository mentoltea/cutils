#include "../test_utility.c"
#include "../darray.h"

int main() {
    array_int array = {0};

    da_free(array);
    assert(array.items == 0);
    assert(array.count == 0);
    assert(array.capacity == 0);
    assert(free_calls == 0);
    
    array.items = malloc(sizeof(int)*5);
    array.count = 5;
    array.capacity = 5;
    
    da_free(array);
    assert(array.items == 0);
    assert(array.count == 0);
    assert(array.capacity == 0);
    assert(free_calls == 1);

    return 0;
}