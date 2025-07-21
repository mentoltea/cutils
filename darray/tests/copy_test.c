#include "../test_utility.c"
#include "../darray.h"

int main() {
    array_int array = {0};
    da_appends(array, int, 0,1,2,3,4);
    assert(array.count == 5);

    array_int array2 = {0};
    da_copy(array2, array);

    assert(array.count == array2.count);
    for (int i=0; i< array.count; i++) {
        assert(array.items[i] == array2.items[i]);
    }

    return 0;
}