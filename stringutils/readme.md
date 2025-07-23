# StringUtils - tools for strings in C
## Usage
To include implementation define `CUTILS_STRINGUTILS_IMPL` and include header where you want implementation to go:  
```C
...
#define CUTILS_STRINGUTILS_IMPL
#include "stringutils.h"
...
```

## Parameters
Parameters are passed as macros definitions.

- `CUTILS_STRINGUTILS_ALLOCATOR`  
Allocator. By default - `malloc`.

- `CUTILS_STRINGUTILS_DEALLOCATOR`  
Deallocator. By default - `free`.

- `CUTILS_STRINGUTILS_MEMCPY`  
Memcopy function. By default - `memcpy`.

## Tests
To build & run tests enter `make` in command line.

---

## Utilities

- ### General tools
	- `char *temp_sprintf(char* format, ...)`  
	Formats string with passed arguments & returns formatted one.

	- `char *make_terminated(char* string, size_t length)`  
	Copies `length` characters from the given buffer `string` into a string and terminates it's end with '\0'. Returns terminated string.

- ### String Builder
    Represents linked list of string chunks to collect & build one string from them.
    ```C
    typedef struct StringChunk {
        struct StringChunk* prev;
        struct StringChunk* next;
        char* item;
        // length withOUT '\0'
        size_t length;
    } StringChunk;

    typedef struct {
        StringChunk* first;
        StringChunk* last;
        size_t count;
    } StringBuilder;
    ```
    Functionality:  

    - `void sb_append(StringBuilder *sb, char* string)`  
    Copies `string` & appends to end of the list.

    - `void sb_appends(StringBuilder *sb, char* string, size_t length);`  
    Copies string from buffer with `make_terminated` & appends to end of the list.

    - `void sb_appendf(StringBuilder *sb, char* format, ...);`  
    Formats string with passed arguments & appends formatted one to end of the list.

    - `void sb_free(StringBuilder *sb);`  
    Frees string builder (both copied strings & list infrastructure) and sets it to `{0}`.

    - `size_t sb_length(StringBuilder *sb);`  
    Returns the sum length of all string chunks (*EXCLUDING '\0's* - only the data length itself).

    - `char* sb_make_string(StringBuilder *sb);`  
    Constructs string from string chunks & flushes (frees) string builder.

    - `char* sb_make_string_nofree(StringBuilder *sb);`  
    Constructs string from string chunks, but doesn't flush (free) string builder.

    You can find examples of using it in [string builder tests](./tests/sb_test.c).

---
## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://t.me/lacus_lacrimalis) : @lacus_lacrimalis