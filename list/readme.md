# List - linked lists in C
## Usage
Library consists only of macros - so you just need to include it.
No need to worry where implementation goes.

Lists are compatible with any structures like  
```C
struct List {
    ...
    Node* first;
    Node* last;
    size_t count;
    ...
};

struct Node {
    ...
    Node* prev;
    Node* next;
    T value;
    ...
};
```
where `T` can be any sized type (any type except the void).

### Example
```C
#include "list.h"

typedef struct NodeInt {
    struct NodeInt* prev;
    struct NodeInt* next;
    int item;
} NodeInt;

typedef struct {
    NodeInt* first;
    NodeInt* last;
    size_t count;
} ListInt;

int main() {
    ListInt list1 = {0};
    ListInt list2 = {0};

    for (int i=0; i<11; i++) {
        da_append_back(list1, NodeInt, i);
    }
    da_pop(list1, NodeInt, list1.count-1);

    for (int i=11; i<20; i++) {
        da_append_back(list2, NodeInt, i);
    }
    
    da_concat(ListInt, NodeInt, list1, list2);

    da_free(list1);
    da_free(list2);
    return 0;
}
```

## Functionality

- `ll_append_back(ll, NodeType, value)`  
Appends value to the end of the list.

- `ll_append_front(ll, NodeType, value)`  
Appends value to the beginning of the list.

- `ll_copy(ll_to, ll_from, NodeType)`  
Copies one list into another.

- `ll_concat(ListType, NodeType, ll1, ll2)`  
Concatinates two lists into one and saves to the first list.  
Example:  
list1 = [1, 2, 3]  
list2 = [4, 5, 6]  
-- Concatination -->  
list1 = [1, 2, 3, 4, 5, 6]  
list2 = [4, 5, 6]  

- `ll_pop(ll, NodeType, index)`  
Pops (removes) element from the given index.

- `ll_foreach(NodeType, iterator, ll)`  
Used for iterating list by reference. `iterator` is name of variable used for iterating.  
The variable itself *is a pointer to a node*.  

- `ll_free(ll)`  
Frees all the nodes of the list and sets it to `{0}`.

- `ll_reverse(ll, NodeType)`  
Reverses list.  
[1, 2, 3] -> [3, 2, 1]

## Parameters
Parameters are passed as macros definitions.

- `CUTILS_LIST_ALLOCATOR`  
Allocator. By default - `malloc`.

- `CUTILS_LIST_DEALLOCATOR`  
Deallocator. By default - `free`.

- `CUTILS_LIST_MEMCPY`  
Memcopy function. By default - `memcpy`.

## Tests
To build & run tests enter `make` in command line.

## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://t.me/lacus_lacrimalis) : @lacus_lacrimalis