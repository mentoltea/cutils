#define CUTILS_HASHMAP_IMPL


typedef char* charptr;
#define HM_KEY charptr
#define HM_VALUE int
#include "hashmap.h"


#undef CUTILS_HASHMAP
#define CUTILS_HASHMAP_IMPL
#undef HM_KEY
#undef HM_VALUE
#define HM_KEY int
#define HM_VALUE size_t
#include "hashmap.h"

#include "stdio.h"
#include <time.h>

size_t hashfunc_str(charptr* strptr) {
    char *str = *strptr;
    
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

size_t hashfunc_sizet(int *elem) {
    return (size_t)*elem;
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


    {
        HashMap(charptr, int) hm = {0};
        printf("HashMap(charptr, int)\n");
        printf("Press enter...\n");
        getc(stdin);
    
        hm_init(charptr, int)(&hm, hashfunc_str);
        hm.keyequal = &hm_string_equal;
        hm.keycopy = &hm_string_copy;
    
        for (int i=0; i<300; i++) {
            size_t rand_len = rand() % 15;
            char* rand_str = random_string(rand_len);
            int rand_val = rand() % 5000;
            
            int *ptr = hm_at(charptr, int)(&hm, rand_str);
            if (ptr != NULL) {
                printf("Keys are the same. Editing instead of pushing\n");
                *ptr = rand_val;
                free(rand_str);
            } else {
                hm_push(charptr, int)(&hm, rand_str, rand_val);
            }
        }
    
        
        printf("Hashmap has %ld elements\n", hm.size);
        printf("Press enter...\n");
        getc(stdin);
        
        hm_foreach_start(charptr, int, pair, hm) {
            printf("%s : %d\n", pair->key, pair->value);
            free(pair->key);
        } hm_foreach_end
    
        hm_free(charptr, int)(&hm);
    
        printf("OK\n");
        printf("Press enter...\n");
        getc(stdin);
    }


    {
        HashMap(int, size_t) hm = {0};
        printf("HashMap(int, size_t)\n");
        printf("Press enter...\n");
        getc(stdin);
    
        hm_init(int, size_t)(&hm, hashfunc_sizet);
    
        for (int i=0; i<300; i++) {
            int rand_val = rand() % 5000;
            hm_set_or_push(int, size_t)(&hm, i, (size_t) rand_val);
        }

        for (int i=0; i<300; i++) {
            int rand_val = i;
            hm_set_or_push(int, size_t)(&hm, i, (size_t) rand_val);
        }
        
        printf("Hashmap has %ld elements\n", hm.size);
        printf("Press enter...\n");
        getc(stdin);
    
        hm_foreach_start(int, size_t, pair, hm) {
            printf("%d : %ld\n", pair->key, pair->value);
        } hm_foreach_end
    
        hm_free(int, size_t)(&hm);
    
        printf("OK\n");
        printf("Press enter...\n");
        getc(stdin);
    }

    printf("Success\n");
    return 0;
}