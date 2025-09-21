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