#include "defer.h"
#include "stdlib.h"
#include "stdio.h"

int some_func(int a) {
DEFERABLE(
    int result = -1;
    char* buffer = NULL;
)
DEFER (
    printf("Result: %s\n", buffer);
    if (buffer) free(buffer);
    return result;
)
BODY (
    if (a <= 0) {
        result = -1;
        dreturn;
    }
    printf("Work...\n");
    buffer = malloc((a + 1) * sizeof(char));
    for (int i=0; i<a; i++) {
        buffer[i] = '0' + i;
    }
    buffer[a] = '\0';
    result = a;
    dreturn;
)
}

int main() {

    some_func(-15);
    other_func(2);
    some_func(10);

    return 0;
}