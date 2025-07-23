#include "../test_utility.c"
#define CUTILS_STRINGUTILS_IMPL
#include "../stringutils.h"

int main() {
    char f0[] = "No format";

    char f1[] = "Format %d";
    
    char f2[] = "Format %s";
    char s2[] = "some_string";

    char* r0 = temp_sprintf(f0);
    assert( strlen(r0) == strlen(f0) );
    assert( strcmp(r0, f0) == 0 );

    char* r1 = temp_sprintf(f1, 123);
    assert( strlen(r1) == strlen(f1) + 1 );

    char* r2 = temp_sprintf(f2, s2);
    assert( strlen(r2) == strlen(f2) - 2 + strlen(s2) );
    size_t r2_length = strlen(r2);
    size_t f2_length = strlen(f2);
    for (int i=0; i < r2_length; i++) {
        if (i < f2_length-2) {
            assert(r2[i] == f2[i]);
        } else {
            assert(r2[i] == s2[i - f2_length + 2]);
        }
    }

    return 0;
}