#ifndef CUTILS_HASHMAP
#define CUTILS_HASHMAP

#define VA_NARGS(...) VA_NARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1)
#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N


#define TEMPLATE(...) TEMPLATE_DISPATCH(VA_NARGS(__VA_ARGS__), __VA_ARGS__)
#define TEMPLATE_DISPATCH(n, ...) TEMPLATE_DISPATCH_(n, __VA_ARGS__)
#define TEMPLATE_DISPATCH_(n, ...) TEMPLATE##n(__VA_ARGS__)

#define TEMPLATE1(T1) template_##T1          
#define TEMPLATE2(T1, T2) template_##T1##_##T2
#define TEMPLATE3(T1, T2, T3) template_##T1##_##T2##_##T3
#define TEMPLATE4(T1, T2, T3, T4) template_##T1##_##T2##_##T3##_##T4
#define TEMPLATE5(T1, T2, T3, T4, T5) template_##T1##_##T2##_##T3##_##T4##_##T5



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
typedef char*  charptr;
#define HM_KEY charptr
#endif

#ifndef HM_VALUE
#define HM_VALUE int
#endif

typedef struct {
    HM_KEY key;
    HM_VALUE value;
} TEMPLATE(hm_pair, HM_KEY, HM_VALUE);


typedef struct {
    TEMPLATE(hm_pair, HM_KEY, HM_VALUE) *items;
    size_t count;
    size_t capacity;
} TEMPLATE(hm_da, HM_KEY, HM_VALUE);



typedef size_t (*TEMPLATE(hashfunc_t, HM_KEY))(HM_KEY*);

typedef bool (*TEMPLATE(keyequal_t, HM_KEY))(HM_KEY*,  HM_KEY*);

typedef HM_KEY (*TEMPLATE(keycopy_t, HM_KEY))(HM_KEY*);

typedef HM_VALUE (*TEMPLATE(valuecopy_t, HM_VALUE))(HM_VALUE*);

typedef struct {
    size_t size; // number of elements
    TEMPLATE(hashfunc_t, HM_KEY) hashfunc;
    
    // optional
    TEMPLATE(keyequal_t, HM_KEY) keyequal;
    TEMPLATE(keycopy_t, HM_KEY) keycopy;
    TEMPLATE(valuecopy_t, HM_VALUE) valuecopy;
    
    // For internal usage
    
    // for darray
    TEMPLATE(hm_da, HM_KEY, HM_VALUE) *items;
    //   [0]      [1]     [2] ... [n]
    //    |        |
    // (k1,e11) (k2,e21)  ...
    // (k2,e12) (k2,e22) 
    //   ...              ...
    size_t count;
    
    // for realloc
    size_t max_count_per_node;
    size_t count_non_empty_nodes;
} TEMPLATE(HashMap, HM_KEY, HM_VALUE);

#define HashMap(KEY, VALUE) TEMPLATE(HashMap, KEY, VALUE)

#define hm_init(KEY, VALUE)     TEMPLATE(inner_hm_init, KEY, VALUE)
#define hm_push(KEY, VALUE)     TEMPLATE(inner_hm_push, KEY, VALUE)
#define hm_at(KEY, VALUE)       TEMPLATE(inner_hm_at,   KEY, VALUE)
#define hm_remove(KEY, VALUE)   TEMPLATE(inner_hm_remove, KEY, VALUE)
#define hm_free(KEY, VALUE)     TEMPLATE(inner_hm_free, KEY, VALUE)
#define hm_copy(KEY, VALUE)     TEMPLATE(inner_hm_copy, KEY, VALUE)
#define hm_update_statistics(KEY, VALUE)     TEMPLATE(inner_hm_update_statistics, KEY, VALUE)
#define hm_realloc_if_needed(KEY, VALUE)     TEMPLATE(inner_hm_realloc_if_needed, KEY, VALUE)
#define hm_realloc(KEY, VALUE)     TEMPLATE(inner_hm_realloc, KEY, VALUE)


void TEMPLATE(inner_hm_init, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, TEMPLATE(hashfunc_t, HM_KEY) hashfunc);
void TEMPLATE(inner_hm_push, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key, HM_VALUE value);
HM_VALUE* TEMPLATE(inner_hm_at, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key);
bool TEMPLATE(inner_hm_remove, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key);
void TEMPLATE(inner_hm_free, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm);
void TEMPLATE(inner_hm_copy, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *dest, TEMPLATE(HashMap, HM_KEY, HM_VALUE) *src);

void TEMPLATE(inner_hm_update_statistics, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm);
void TEMPLATE(inner_hm_realloc_if_needed, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm);
void TEMPLATE(inner_hm_realloc, HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm);

#define hm_foreach_start(KEY, VALUE, it, hm) \
    for (size_t __index=0; __index<(hm).count; __index++) { \
        for (size_t __i=0; __i<(hm).items[__index].count; __i++) { \
            TEMPLATE(hm_pair, KEY, VALUE) *(it) = &(((hm).items)[__index].items)[__i]; 


#define hm_foreach_end }}



bool hm_string_equal( char** s1,  char** s2);
char* hm_string_copy( char** s);


#endif // CUTILS_HASHMAP

#ifdef CUTILS_HASHMAP_IMPL

#ifndef HM_STRING_FUNCS_IMPL
#define HM_STRING_FUNCS_IMPL
bool hm_string_equal( char** s1,  char** s2) {
    bool result = !strcmp(*s1, *s2);
    return result;
}
char* hm_string_copy( char** s) {
    char *result = strdup(*s);
    return result;
}
#endif // HM_STRING_FUNCS_IMPL


#define START_CAP 128

#define CAP_FACTOR 1.5

#define REALLOC_FRAC_TOTAL 0.75
#define REALLOC_NUM_PER_NODE 8

void hm_init(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, TEMPLATE(hashfunc_t, HM_KEY) hashfunc) {
    hm->hashfunc = hashfunc;
    
    hm->items = calloc(START_CAP, sizeof(TEMPLATE(hm_da, HM_KEY, HM_VALUE)));
    hm->count = START_CAP;

    hm->max_count_per_node = 0;
    hm->count_non_empty_nodes = 0;
}

void hm_push(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key, HM_VALUE value) {
    hm_realloc_if_needed(HM_KEY, HM_VALUE)(hm);
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;

    TEMPLATE(hm_da, HM_KEY, HM_VALUE)* da = &hm->items[index];
    TEMPLATE(hm_pair, HM_KEY, HM_VALUE) pair = {.key = key, .value = value};
    
    if (hm->keyequal) {
        da_foreach(TEMPLATE(hm_pair, HM_KEY, HM_VALUE), ptr, *da) {
            if (hm->keyequal(&ptr->key, &key)) {
                // ptr->value = value;
                // return;
                fprintf(stderr, "Pushed key already exists\n");
                abort();
            }
        }
    } else {
        da_foreach(TEMPLATE(hm_pair, HM_KEY, HM_VALUE), ptr, *da) {
            if (ptr->key == key) {
                // ptr->value = value;
                // return;
                fprintf(stderr, "Pushed key already exists\n");
                abort();
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

HM_VALUE* hm_at(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key) {
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;
    TEMPLATE(hm_da, HM_KEY, HM_VALUE)* da = &hm->items[index];
    size_t i;
    
    if (hm->keyequal) {
        for (i=0; i<da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE)* pair = &da->items[i];
            if ( hm->keyequal( &pair->key, &key ) ) {
                break;
            }
        }
    } else {
        for (i=0; i<da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE)* pair = &da->items[i];
            if ( pair->key == key ) {
                break;
            }
        }
    }
    
    if (i == da->count) return NULL;

    return &(da->items[i].value);
}

bool hm_remove(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm, HM_KEY key) {
    size_t hash = hm->hashfunc(&key);
    size_t index = hash % hm->count;
    TEMPLATE(hm_da, HM_KEY, HM_VALUE)* da = &hm->items[index];
    
    size_t i;

    if (hm->keyequal) {
        for (i=0; i<da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE)* pair = &da->items[i];
            if ( hm->keyequal( &pair->key, &key ) ) {
                break;
            }
        }
    } else {
        for (i=0; i<da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE)* pair = &da->items[i];
            if ( pair->key == key ) {
                break;
            }
        }
    }

    if (i == da->count) return false;
    da_pop(*da, i);

    hm_update_statistics(HM_KEY, HM_VALUE)(hm);
    return true;
}

void hm_free(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm) {
    for (size_t index=0; index<hm->count; index++) {
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *da = &hm->items[index];
        da_free(*da);
    }
    if (hm->items) {
        free(hm->items);
    }
    hm->items = NULL;
    hm->count = 0;
}

void hm_copy(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *dest, TEMPLATE(HashMap, HM_KEY, HM_VALUE) *src) {
    hm_free(HM_KEY, HM_VALUE)(dest);
    
    dest->hashfunc = src->hashfunc;
    dest->keyequal = src->keyequal;
    dest->keycopy = src->keycopy;
    dest->valuecopy = src->valuecopy;
    
    dest->items = calloc(src->count, sizeof(TEMPLATE(hm_da, HM_KEY, HM_VALUE)));
    dest->count = src->count;
    
    for (size_t index=0; index<src->count; index++) {
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *dest_da = &dest->items[index];
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *src_da = &src->items[index];
        
        dest_da->capacity = src_da->count;
        dest_da->count = src_da->count;
        if (src_da->count == 0) {
            dest_da->items = NULL;
            continue;
        }
        dest_da->items = malloc(dest_da->capacity * sizeof(TEMPLATE(hm_pair, HM_KEY, HM_VALUE)));
        
        for (size_t i=0; i<src_da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE) *dp = &dest_da->items[i];
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE) *sp = &src_da->items[i];
            
            if (src->keycopy) dp->key = src->keycopy(&sp->key);
            else dp->key = sp->key;
            
            if (src->valuecopy) dp->value = src->valuecopy(&sp->value);
            else dp->value = sp->value;
        }
    }

    hm_update_statistics(HM_KEY, HM_VALUE)(dest);
}

void hm_update_statistics(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm) {
    hm->size=0;
    hm->max_count_per_node = 0;
    hm->count_non_empty_nodes = 0;

    for (size_t index=0; index<hm->count; index++) {
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *da = &hm->items[index];
        hm->size += da->count;
        if (da->count > 0) hm->count_non_empty_nodes++;
        if (da->count > hm->max_count_per_node) hm->max_count_per_node = da->count;        
    }
}

void hm_realloc_if_needed(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm) {
    if (hm->count==0) return;

    double frac_total = (double)hm->count_non_empty_nodes / (double)hm->count;

    if (frac_total >= REALLOC_FRAC_TOTAL || hm->max_count_per_node >= REALLOC_NUM_PER_NODE) {
        hm_realloc(HM_KEY, HM_VALUE)(hm);
    }
}

void hm_realloc(HM_KEY, HM_VALUE)(TEMPLATE(HashMap, HM_KEY, HM_VALUE) *hm) {
    if (hm->count == 0) return;

    size_t new_count = hm->count*CAP_FACTOR;
    TEMPLATE(hm_da, HM_KEY, HM_VALUE) *new_items = calloc(new_count, sizeof(TEMPLATE(hm_da, HM_KEY, HM_VALUE)));

    for (size_t index=0; index<hm->count; index++) {
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *da = &hm->items[index];
        for (size_t i=0; i<da->count; i++) {
            TEMPLATE(hm_pair, HM_KEY, HM_VALUE) *pair = &da->items[i];

            size_t hash = hm->hashfunc(&pair->key);
            size_t new_index = hash % new_count;
            
            TEMPLATE(hm_da, HM_KEY, HM_VALUE) *new_da = &new_items[new_index]; 
            da_append(*new_da, *pair);
        }
    }

    for (size_t index=0; index<hm->count; index++) {
        TEMPLATE(hm_da, HM_KEY, HM_VALUE) *da = &hm->items[index];
        da_free(*da);
    }
    free(hm->items);
    
    hm->items = new_items;
    hm->count = new_count;

    hm_update_statistics(HM_KEY, HM_VALUE)(hm);
}

#endif // CUTILS_HASHMAP_IMPL