# HashMap
## Notes

1. Supports templating through macros. See [Parameters](#parameters) and [Usage](#usage) for description.

2. Hashmap depends on [dynamic arrays](../darray/).

3. Hashmaps support using custom equal and copy functions for structures that can't be properly compared and copied with built-in `=`. However, custom deinitialization functions are not supported, because it is assumed you to **deinitialize elements manually** before freeing map.

## Parameters

`HM_KEY` & `HM_VALUE` macros. If not defined, uses `charptr` (`char*`) and `int` correspondingly.

Custom memory managers available through macros `CUTILS_HASHMAP_ALLOCATOR`, `CUTILS_HASHMAP_CALLOCATOR`, `CUTILS_HASHMAP_DEALLOCATOR` (that are similar to `malloc`, `calloc` and `free` correspondingly)

**Important:** `HM_KEY` & `HM_VALUE` must be simple identificators (for example, `int` or `MyStruct`). If your type does not meet this criteria (pointers, structs, enums), use `typedef` to define them as simple identificators. Example with `char*` [here](./test.c).

### Required

* `hashfunc_t hashfunc` - pointer to hashing function of type `size_t ()(HM_KEY*)`

### Optional

* `keyequal_t keyequal` - pointer to key equality function of type `bool ()(HM_KEY*, HM_KEY*)`

* `keycopy_t keycopy` - pointer to key copying function of type `HM_KEY ()(HM_KEY*)`

* `valuecopy_t valuecopy` - pointer to value copying function of type `HM_VALUE ()(HM_VALUE*)`

## Functionality
Note: all functions listed below are actually macros to provide simple templates. These macros are created for the simplicity of usage, to not enter names like `template_inner_hm_init_charptr_int`.

### Initialization, copying & freeing
* `void hm_init(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm, hashfunc_t hashfunc)`
* `void hm_copy(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *dest, HashMap(HM_KEY, HM_VALUE) *src)`
* `void hm_free(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm)`

### Element manipulations
* `void hm_push(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm, HM_KEY key, HM_VALUE value)` - aborts if element with such key already exists
* `void hm_set_or_push(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm, HM_KEY key, HM_VALUE value)`
* `bool hm_remove(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm, HM_KEY key)`
* `HM_VALUE* hm_at(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm, HM_KEY key)` - returns `NULL` if no element with such key found

### Iterating
* `hm_foreach_start(HM_KEY, HM_VALUE, iterator, hm)`
* `hm_foreach_end`

### Mostly internal functions
* `void hm_update_statistics(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm)`
* `void hm_realloc_if_needed(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm)`
* `void hm_realloc(HM_KEY, HM_VALUE)(HashMap(HM_KEY, HM_VALUE) *hm)`

### Predefined functions for strings
* * `bool hm_string_equal(char** s1, char** s2)`
* * `char* hm_string_copy(char** s)` - allocates memory

## Usage
Ordinary header only library. To include implementation predefine `CUTILS_HASHMAP_IMPL`.  
If you want to include it again with different template parameters, first undefine `CUTILS_HASHMAP`.

## Example
Can be found [here](./test.c)

## Consistency & tests
At the current moment, the are no test made for this project, but the [example](./test.c) was fully checked by valgrind and there were no found memory leaks.

## Authors
*Agoev T* - [github](https://github.com/mentoltea) | [telegram](https://t.me/lacus_lacrimalis) : @lacus_lacrimalis