# HashMap
## Notes

1. Currently using hashmaps of different types inside one project **is not supported** due to lack of templatability. In future, I might introduce macros like `HM_DECLARATION(key, value)` and `HM_IMPLEMENTATION(key, value)` or find another way to allow templating.

2. Hashmap depends on [dynamic arrays](../darray/).

3. Hashmaps supports using custom equal and copy functions for structures that can't be properly compared and copied with built-in `=`. However, custom deinitialization functions are not supported, because it is assumed you to **deinitialize elements manually** before freeing map.

## Parameters

`HM_KEY` & `HM_VALUE` macros. If not defined, uses `char*` and `int` correspondingly.

### Required

* `hashfunc_t hashfunc` - pointer to hashing function of type `size_t ()(HM_KEY*)`

### Optional

* `keyequal_t keyequal` - pointer to key equality function of type `bool ()(HM_KEY*, HM_KEY*)`

* `keycopy_t keycopy` - pointer to key copying function of type `HM_KEY ()(HM_KEY*)`

* `valuecopy_t valuecopy` - pointer to value copying function of type `HM_VALUE ()(HM_VALUE*)`

## Functionality

### Initialization, copying & freeing
* `void hm_init(HashMap *hm, hashfunc_t hashfunc)`
* `void hm_copy(HashMap *dest, HashMap *src)`
* `void hm_free(HashMap *hm)`

### Element manipulations
* `void hm_push(HashMap *hm, HM_KEY key, HM_VALUE value)`
* `bool hm_remove(HashMap *hm, HM_KEY key)`
* `HM_VALUE* hm_at(HashMap *hm, HM_KEY key)` - returns `NULL` if no element with such key found

### Iterating
* `hm_foreach_start(iterator, hm)`
* `hm_foreach_end`

### Mostly internal functions
* `void hm_update_statistics(HashMap *hm)`
* `void hm_realloc_if_needed(HashMap *hm)`
* `void hm_realloc(HashMap *hm)`

### Predefined functions for strings
* * `bool hm_string_equal(char** s1, char** s2)`
* * `char* hm_string_copy(char** s)` - allocates memory

## Usage
Ordinary header only library. To include implementation predefine `CUTILS_HASHMAP_IMPL`

## Example
``` C
#define CUTILS_HASHMAP_IMPL
#include "hashmap.h"
#include "stdio.h"
#include <time.h>

size_t hashfunc(char ** strptr) {
    char *str = *strptr;
    
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

char* random_string(size_t len) {
    char *buffer = malloc(len+1);
    for (size_t i=0; i<len; i++) {
        char c;
        do {
            c = rand();
        } while (c < 32);
        buffer[i] = c;
    }
    buffer[len] = '\0';
    return buffer;
}

int main() {
    srand(time(NULL));
    HashMap hm = {0};

    hm_init(&hm, hashfunc);
    hm.keyequal = &hm_string_equal;
    hm.keycopy = &hm_string_copy;

    for (int i=0; i<300; i++) {
        size_t rand_len = rand() % 15;
        char* rand_str = random_string(rand_len);

        int rand_val = rand() % 5000;
        hm_push(&hm, rand_str, rand_val);
    }

    getc(stdin);

    hm_foreach_start(pair, hm) {
        printf("%s : %d\n", pair->key, pair->value);
        free(pair->key);
    } hm_foreach_end

    hm_free(&hm);

    printf("OK\n");
    return 0;
}
```

## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://t.me/lacus_lacrimalis) : @lacus_lacrimalis