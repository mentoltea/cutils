#ifndef CUTILS_STRINGUTILS_STRING_BUILDER
#define CUTILS_STRINGUTILS_STRING_BUILDER

#define CUTILS_STRINGUTILS_SKIP_IMPL
#include "../../list/list.h"
#include "../stringutils.h"
#undef CUTILS_STRINGUTILS_SKIP_IMPL

typedef struct StringChunk {
    struct StringChunk* prev;
    struct StringChunk* next;
    char* item;
    // length withOUT '\0'
    size_t length;    
} StringChunk;

typedef struct {
    StringChunk* first;
    StringChunk* last;
    size_t count;
} StringBuilder;

void sb_append(StringBuilder *sb, char* string);

void sb_appends(StringBuilder *sb, char* string, size_t length);

void sb_appendf(StringBuilder *sb, char* format, ...);

void sb_free(StringBuilder *sb);

// length of concatinated string (EXCLUDING ending '\0')
size_t sb_length(StringBuilder *sb);

char* sb_make_string(StringBuilder *sb);

char* sb_make_string_nofree(StringBuilder *sb);

#endif // CUTILS_STRINGUTILS_STRING_BUILDER