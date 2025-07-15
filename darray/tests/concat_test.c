#include "../test_utility.c"
#include "../darray.h"

int main() {
    {
        array_int arr1 = {0};
        array_int arr2 = {0};

        da_appends(arr1, int, 0, 1, 2, 3, 4);
        size_t oldcount = arr1.count;
        da_appends(arr2, int, 5, 6, 7, 8, 9);

        da_concat(arr1, arr2);
        assert(oldcount + arr2.count == arr1.count);
        for (int i=0; i<arr1.count; i++) {
            assert(arr1.items[i] == i);
        }

        da_free(arr1);
        da_free(arr2);
    }
    {
        array_int arr1 = {0};
        array_int arr2 = {0};

        da_appends(arr2, int, 5, 6, 7, 8, 9);

        da_concat(arr1, arr2);
        assert(arr2.count == arr1.count);
        for (int i=0; i<arr1.count; i++) {
            assert(arr1.items[i] == arr2.items[i]);
        }

        da_free(arr1);
        da_free(arr2);
    }
    {
        array_int arr1 = {0};
        array_int arr2 = {0};

        da_appends(arr1, int, 0, 1, 2, 3, 4);
        size_t oldcount = arr1.count;

        da_concat(arr1, arr2);
        assert(oldcount == arr1.count);
        for (int i=0; i<arr1.count; i++) {
            assert(arr1.items[i] == i);
        }

        da_free(arr1);
        da_free(arr2);
    }
    {
        array_int arr1 = {0};
        array_int arr2 = {0};

        da_concat(arr1, arr2);
        assert(arr1.count == 0);

        da_free(arr1);
        da_free(arr2);
    }

    return 0;
}