# DArray - dynamic arrays in C
## Usage
Library consists only of macros - so you just need to include it.
No need to worry where implementation goes.

Darrays are compatible with any structures like  
```C
struct S {
    ...
    T* items;
    size_t count;
    size_t capacity;
    ...
}
```
where `T` can be any sized type (any type except the void).

### Example
```C
#include "darray.h"

typedef struct {
    int* items;
    size_t count;
    size_t capacity;
} array_int;

int main() {
    array_int array1 = {0};
    array_int array2 = {0};

    for (int i=0; i<11; i++) {
        da_append(array1, i);
    }
    da_pop(array1, array1.count-1);

    da_appends(array2, int, 11, 12, 13, 14, 15);
    
    da_concat(array1, array2);

    da_free(array1);
    da_free(array2);
    return 0;
}
```

## Functionality

- `da_append(da, element)`  
Appends one element to array.

- `da_appends(da, type, ...)`  
Appends many elements to array. Is implemented through making a buffer of given elements and iteratively adding them with `da_append`, so *can be used only with constant initialization*.

- `da_concat(da1, da2)`  
Concatinates two arrays into one and saves to the first array.  
Example:  
arr1 = [1, 2, 3]  
arr2 = [4, 5, 6]  
-- Concatination -->  
arr1 = [1, 2, 3, 4, 5, 6]  
arr2 = [4, 5, 6]  

- `da_pop(da, index)`  
Pops (removes) element from the given index.

- `da_foreach(type, iterator, da)`  
Used for iterating arrays by reference. `iterator` is name of variable used for iterating.  
The variable itself *is a pointer* to element.


- `da_free(da)`  
Frees array if it was owning any memory and sets it to `{0}`.

## Parameters
Parameters are passed as macros definitions.

- `CUTILS_DARRAY_ALLOCATOR`  
Allocator. By default - `malloc`.

- `CUTILS_DARRAY_DEALLOCATOR`  
Deallocator. By default - `free`.

- `CUTILS_DARRAY_MEMCPY`  
Memcopy function. By default - `memcpy`.

- `CUTILS_DARRAY_DEFAULT_SIZE`  
Default capacity to set new(empty) arrays. By default - 10.

- `CUTILS_DARRAY_DEFAULT_EXPANSION`  
Default capacity factor of expanding arrays. By default - 2.

## Tests
To build & run tests enter `make` in command line.

## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://web.telegram.org/k/#@lacus_lacrimalis) : @lacus_lacrimalis