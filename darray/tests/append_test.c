#include "../test_utility.c"

#define CUTILS_DARRAY_DEFAULT_SIZE 10
#define CUTILS_DARRAY_DEFAULT_EXPANSION 1.5

#include "../darray.h"

int main() {
    {
        array_int array = {0};
        for (int i=0; i<10; i++) {
            da_append(array, i);
        }
        assert(array.items != NULL);
        assert(array.count == 10);
        assert(array.capacity == 10);
        assert(malloc_calls == 1);
        for (int i=0; i<array.count; i++) {
            assert(array.items[i] == i);
        }
        
        for (int i=10; i<15; i++) {
            da_append(array, i);
        }
        assert(array.items != NULL);
        assert(array.count == 15);
        assert(array.capacity == 15);
        assert(malloc_calls == 2);
        for (int i=0; i<array.count; i++) {
            assert(array.items[i] == i);
        }
        
        da_free(array);
    }

    {
        array_int array = {0};
        da_appends(array, int, 0,1,2,3,4,5,6,7,8,9,10,11,12,13);
        assert(array.count == 14);
        for (int i=0; i<array.count; i++) {
            assert(array.items[i] == i);
        }

        da_free(array);
    }

    return 0;
}