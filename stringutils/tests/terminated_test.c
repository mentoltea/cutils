#include "../test_utility.c"
#define CUTILS_STRINGUTILS_IMPL
#include "../stringutils.h"

int main() {
    char bigbuff[] = "0123456789ABCDEFG";

    char* term5 = make_terminated(bigbuff, 5);
    char* term5_5 = make_terminated(bigbuff + 5, 5);
    char* term10 = make_terminated(bigbuff, 10);
    char* term17 = make_terminated(bigbuff, 17);

    for (int i=0; i<5; i++) {
        assert(term5[i] == bigbuff[i]);
    }
    assert(term5[5] == '\0');

    for (int i=0; i<5; i++) {
        assert(term5_5[i] == bigbuff[i + 5]);
    }
    assert(term5_5[5] == '\0');

    for (int i=0; i<10; i++) {
        assert(term10[i] == bigbuff[i]);
    }
    assert(term10[10] == '\0');

    for (int i=0; i<17; i++) {
        assert(term17[i] == bigbuff[i]);
    }
    assert(term17[17] == '\0');

    return 0;
}