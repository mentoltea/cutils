#include "../test_utility.c"
#define CUTILS_STRINGUTILS_IMPL
#include "../stringutils.h"

void test_sb_append() {
    StringBuilder sb = {0};
    char s1[] = "String1";
    char s2[] = "String2";

    sb_append(&sb, s1);
    assert(sb.count == 1);
    assert(sb.first == sb.last);
    assert(strcmp(sb.first->item, s1) == 0);
    
    
    sb_append(&sb, s2);
    assert(sb.count == 2);
    assert(strcmp(sb.first->item, s1) == 0);
    assert(strcmp(sb.last->item, s2) == 0);
    
    sb_free(&sb);
}

void test_sb_appends() {
    StringBuilder sb = {0};
    char buffer[] = "0123456789";

    sb_appends(&sb, buffer, 5);
    assert(sb.count == 1);
    assert(sb.first == sb.last);
    for (int i=0; i<5; i++) {
        assert(buffer[i] == sb.first->item[i]);
    }

    sb_appends(&sb, buffer + 5, 5);
    assert(sb.count == 2);
    for (int i=0; i<5; i++) {
        assert(buffer[i + 5] == sb.last->item[i]);
    }

    sb_free(&sb);
}

void test_sb_appendf() {
    StringBuilder sb = {0};

    char f0[] = "No format";
    
    char f1[] = "Format %d";
    int a1 = 123;

    char f2[] = "String format: %s";
    char s2[] = "string";

    sb_appendf(&sb, f0);
    assert(strcmp(sb.first->item, f0) == 0);
    assert(sb.last->length == strlen(sb.last->item));

    sb_appendf(&sb, f1, a1);
    assert(strlen(sb.last->item) == strlen(f1) - 2 + 3);
    assert(sb.last->length == strlen(sb.last->item));
    
    sb_appendf(&sb, f2, s2);
    assert(strlen(sb.last->item) == strlen(f2) - 2 + strlen(s2));
    assert(sb.last->length == strlen(sb.last->item));

    sb_free(&sb);
}

void test_sb_free() {
    StringBuilder sb = {0};
    size_t old_free_calls = free_calls;

    sb_append(&sb, "Const string");
    sb_appends(&sb, "Const string slice", 12);
    sb_appendf(&sb, "Format string %d %ld %lld", 12, 14, 16);

    sb_free(&sb);
    assert(malloc_calls == free_calls);
    assert(free_calls == old_free_calls + 3);
}

void test_sb_length() {
    StringBuilder sb = {0};

    char s1[] = "123456";
    char s2[] = "abcdef";
    char s3[] = "1curtdfyvgukhbjinkom\\";

    sb_append(&sb, s1);
    sb_append(&sb, s2);
    sb_append(&sb, s3);

    assert(sb_length(&sb) == strlen(s1) + strlen(s2) + strlen(s3));

    sb_free(&sb);
}

void test_sb_make_string() {
    StringBuilder sb = {0};

    char s1[] = "123456";
    char s2[] = "abcdef";
    char s3[] = "1curtdfyvgukhbjinkom\\";

    sb_append(&sb, s1);
    sb_append(&sb, s2);
    sb_append(&sb, s3);

    char* string = sb_make_string(&sb);
    assert(sb.count==0);
    assert(sb.first==sb.last);
    assert(sb.first==NULL);

    size_t ss1 = strlen(s1);
    size_t ss2 = strlen(s2);
    size_t ss3 = strlen(s3);

    for (int i=0; i<ss1; i++) {
        assert(string[i] == s1[i]);
    }

    for (int i=0; i<ss2; i++) {
        assert(string[ss1 + i] == s2[i]);
    }

    for (int i=0; i<ss3; i++) {
        assert(string[ss1 + ss2 + i] == s3[i]);
    }

    CUTILS_STRINGUTILS_DEALLOCATOR(string);
    sb_free(&sb);
}

void test_sb_make_string_nofree() {
    StringBuilder sb = {0};

    char s1[] = "123456";
    char s2[] = "abcdef";
    char s3[] = "1curtdfyvgukhbjinkom\\";

    sb_append(&sb, s1);
    sb_append(&sb, s2);
    sb_append(&sb, s3);

    char* string = sb_make_string_nofree(&sb);
    assert(sb.count!=0);
    assert(sb.first!=sb.last);
    assert(sb.first!=NULL);

    size_t ss1 = strlen(s1);
    size_t ss2 = strlen(s2);
    size_t ss3 = strlen(s3);

    for (int i=0; i<ss1; i++) {
        assert(string[i] == s1[i]);
    }

    for (int i=0; i<ss2; i++) {
        assert(string[ss1 + i] == s2[i]);
    }

    for (int i=0; i<ss3; i++) {
        assert(string[ss1 + ss2 + i] == s3[i]);
    }

    CUTILS_STRINGUTILS_DEALLOCATOR(string);
    sb_free(&sb);
}

int main() {

    test_sb_append();               assert(malloc_calls == free_calls);
    test_sb_appends();              assert(malloc_calls == free_calls);
    test_sb_appendf();              assert(malloc_calls == free_calls);
    test_sb_free();                 assert(malloc_calls == free_calls);
    test_sb_length();               assert(malloc_calls == free_calls);
    test_sb_make_string();          assert(malloc_calls == free_calls);
    test_sb_make_string_nofree();   assert(malloc_calls == free_calls);

    return 0;
}