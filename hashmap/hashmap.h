#ifndef CUTILS_HASHMAP
#define CUTILS_HASHMAP

#ifndef CUTILS_HASHMAP_ALLOCATOR
#define CUTILS_HASHMAP_ALLOCATOR malloc
#endif

#ifndef CUTILS_HASHMAP_CALLOCATOR
#define CUTILS_HASHMAP_CALLOCATOR calloc
#endif

#ifndef CUTILS_HASHMAP_DEALLOCATOR
#define CUTILS_HASHMAP_DEALLOCATOR free
#endif

#ifndef CUTILS_HASHMAP_MEMCPY
#define CUTILS_HASHMAP_MEMCPY memcpy
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../darray/darray.h"

#ifndef HM_KEY
#define HM_KEY char*
#endif

#ifndef HM_VALUE
#define HM_VALUE int
#endif

typedef struct {
    HM_KEY key;
    HM_VALUE value;
} _hm_pair;


typedef struct {
    _hm_pair *items;
    size_t count;
    size_t capacity;
} _hm_da;

typedef size_t (*hashfunc_t)(HM_KEY*);

typedef bool (*keyequal_t)(HM_KEY*, HM_KEY*);

typedef HM_KEY (*keycopy_t)(HM_KEY*);
typedef HM_VALUE (*valuecopy_t)(HM_VALUE*);

typedef struct {
    size_t size; // number of elements
    hashfunc_t hashfunc;
    
    // optional
    keyequal_t keyequal;
    keycopy_t keycopy;
    valuecopy_t valuecopy;
    
    // For internal usage
    
    // for darray
    _hm_da *items;
    //   [0]      [1]     [2] ... [n]
    //    |        |
    // (k1,e11) (k2,e21)  ...
    // (k2,e12) (k2,e22) 
    //   ...              ...
    size_t count;
    
    // for realloc
    size_t max_count_per_node;
    size_t count_non_empty_nodes;
} HashMap;

void hm_init(HashMap *hm, hashfunc_t hashfunc);
void hm_push(HashMap *hm, HM_KEY key, HM_VALUE value);
HM_VALUE* hm_at(HashMap *hm, HM_KEY key);
bool hm_remove(HashMap *hm, HM_KEY key);
void hm_free(HashMap *hm);
void hm_copy(HashMap *dest, HashMap *src);

void hm_update_statistics(HashMap *hm);
void hm_realloc_if_needed(HashMap *hm);
void hm_realloc(HashMap *hm);

#define hm_foreach_start(it, hm) \
    for (size_t __index=0; __index<(hm).count; __index++) { \
        for (size_t __i=0; __i<(hm).items[__index].count; __i++) { \
            _hm_pair *(it) = &(hm).items[__index].items[__i]; 


#define hm_foreach_end }}



bool hm_string_equal(char** s1, char** s2);
char* hm_string_copy(char** s);


#endif // CUTILS_HASHMAP

#ifdef CUTILS_HASHMAP_IMPL

bool hm_string_equal(char** s1, char** s2) {
    bool result = !strcmp(*s1, *s2);
    return result;
}
char* hm_string_copy(char** s) {
    char *result = strdup(*s);
    return result;
}


#define START_CAP 128

#define CAP_FACTOR 1.5

#define REALLOC_FRAC_TOTAL 0.75
#define REALLOC_NUM_PER_NODE 8

void hm_init(HashMap *hm, hashfunc_t hashfunc) {
    hm->hashfunc = hashfunc;
    
    hm->items = calloc(START_CAP, sizeof(_hm_da));
    hm->count = START_CAP;

    hm->max_count_per_node = 0;
    hm->count_non_empty_nodes = 0;
}

void hm_push(HashMap *hm, HM_KEY key, HM_VALUE value) {
    hm_realloc_if_needed(hm);
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;

    _hm_da* da = &hm->items[index];
    _hm_pair pair = {.key = key, .value = value};
    
    if (hm->keyequal) {
        da_foreach(_hm_pair, ptr, *da) {
            if (hm->keyequal(&ptr->key, &key)) {
                ptr->value = value;
                return;
            }
        }
    } else {
        da_foreach(_hm_pair, ptr, *da) {
            if (ptr->key == key) {
                ptr->value = value;
                return;
            }
        }
    }

    da_append(*da, pair);
    
    hm->size++;
    if (da->count > hm->max_count_per_node)
        hm->max_count_per_node = da->count;
    if (da->count == 1) 
        hm->count_non_empty_nodes++; 
}

HM_VALUE* hm_at(HashMap *hm, HM_KEY key) {
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;
    _hm_da* da = &hm->items[index];
    size_t i;
    
    if (hm->keyequal) {
        for (i=0; i<da->count; i++) {
            _hm_pair* pair = &da->items[i];
            if ( hm->keyequal( &pair->key, &key ) ) {
                break;
            }
        }
    } else {
        for (i=0; i<da->count; i++) {
            _hm_pair* pair = &da->items[i];
            if ( pair->key == key ) {
                break;
            }
        }
    }
    
    if (i == da->count) return NULL;

    return &(da->items[i].value);
}

bool hm_remove(HashMap *hm, HM_KEY key) {
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;
    _hm_da* da = &hm->items[index];
    
    size_t i;

    if (hm->keyequal) {
        for (i=0; i<da->count; i++) {
            _hm_pair* pair = &da->items[i];
            if ( hm->keyequal( &pair->key, &key ) ) {
                break;
            }
        }
    } else {
        for (i=0; i<da->count; i++) {
            _hm_pair* pair = &da->items[i];
            if ( pair->key == key ) {
                break;
            }
        }
    }

    if (i == da->count) return false;
    da_pop(*da, i);

    hm_update_statistics(hm);
    return true;
}

void hm_free(HashMap *hm) {
    for (size_t index=0; index<hm->count; index++) {
        _hm_da *da = &hm->items[index];
        da_free(*da);
    }
    if (hm->items) {
        free(hm->items);
    }
    hm->items = NULL;
    hm->count = 0;
}

void hm_copy(HashMap *dest, HashMap *src) {
    hm_free(dest);
    
    dest->hashfunc = src->hashfunc;
    dest->keyequal = src->keyequal;
    dest->keycopy = src->keycopy;
    dest->valuecopy = src->valuecopy;
    
    dest->items = calloc(src->count, sizeof(_hm_da));
    dest->count = src->count;
    
    for (size_t index=0; index<src->count; index++) {
        _hm_da *dest_da = &dest->items[index];
        _hm_da *src_da = &src->items[index];
        
        dest_da->capacity = src_da->count;
        dest_da->count = src_da->count;
        if (src_da->count == 0) {
            dest_da->items = NULL;
            continue;
        }
        dest_da->items = malloc(dest_da->capacity * sizeof(_hm_pair));
        
        for (size_t i=0; i<src_da->count; i++) {
            _hm_pair *dp = &dest_da->items[i];
            _hm_pair *sp = &src_da->items[i];
            
            if (src->keycopy) dp->key = src->keycopy(&sp->key);
            else dp->key = sp->key;
            
            if (src->valuecopy) dp->value = src->valuecopy(&sp->value);
            else dp->value = sp->value;
        }
    }

    hm_update_statistics(dest);
}

void hm_update_statistics(HashMap *hm) {
    hm->size=0;
    hm->max_count_per_node = 0;
    hm->count_non_empty_nodes = 0;

    for (size_t index=0; index<hm->count; index++) {
        _hm_da *da = &hm->items[index];
        hm->size += da->count;
        if (da->count > 0) hm->count_non_empty_nodes++;
        if (da->count > hm->max_count_per_node) hm->max_count_per_node = da->count;        
    }
}

void hm_realloc_if_needed(HashMap *hm) {
    if (hm->count==0) return;

    double frac_total = (double)hm->count_non_empty_nodes / (double)hm->count;

    if (frac_total >= REALLOC_FRAC_TOTAL || hm->max_count_per_node >= REALLOC_NUM_PER_NODE) {
        hm_realloc(hm);
    }
}

void hm_realloc(HashMap *hm) {
    if (hm->count == 0) return;
    printf("REALLOCING\n");

    size_t new_count = hm->count*CAP_FACTOR;
    _hm_da *new_items = calloc(new_count, sizeof(_hm_da));

    for (size_t index=0; index<hm->count; index++) {
        _hm_da *da = &hm->items[index];
        for (size_t i=0; i<da->count; i++) {
            _hm_pair *pair = &da->items[i];

            size_t hash = hm->hashfunc(&pair->key);
            size_t new_index = hash % new_count;
            
            _hm_da *new_da = &new_items[new_index]; 
            da_append(*new_da, *pair);
        }
    }

    for (size_t index=0; index<hm->count; index++) {
        _hm_da *da = &hm->items[index];
        da_free(*da);
    }
    free(hm->items);
    
    hm->items = new_items;
    hm->count = new_count;

    hm_update_statistics(hm);
}

#endif // CUTILS_HASHMAP_IMPL