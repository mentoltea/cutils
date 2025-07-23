#ifndef CUTILS_STRINGUTILS
#define CUTILS_STRINGUTILS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef CUTILS_STRINGUTILS_ALLOCATOR
#define CUTILS_STRINGUTILS_ALLOCATOR malloc
#endif // CUTILS_STRINGUTILS_ALLOCATOR

#ifndef CUTILS_STRINGUTILS_DEALLOCATOR
#define CUTILS_STRINGUTILS_DEALLOCATOR free
#endif // CUTILS_STRINGUTILS_DEALLOCATOR

#ifndef CUTILS_STRINGUTILS_MEMCPY
#define CUTILS_STRINGUTILS_MEMCPY memcpy
#endif // CUTILS_STRINGUTILS_MEMCPY

// formats string & writes to temporary buffer 
char *temp_sprintf(char* format, ...);

char *make_terminated(char* string, size_t length);

#include "utils/stringBuilder.h"

#endif // CUTILS_STRINGUTILS

/* --------------------------------------------------------- */

#if defined(CUTILS_STRINGUTILS_IMPL) && !defined(CUTILS_STRINGUTILS_IMPL_INCLUDED) && !defined(CUTILS_STRINGUTILS_SKIP_IMPL)
#define CUTILS_STRINGUTILS_IMPL_INCLUDED

char *make_terminated(char* string, size_t length) {
    char *buffer = CUTILS_STRINGUTILS_ALLOCATOR( (length + 1) * sizeof(char));
    CUTILS_STRINGUTILS_MEMCPY(buffer, string, length * sizeof(char));
    buffer[length] = '\0';
    return buffer;
}

char* temp_sprintf(char* format, ...) {
    va_list arglist;
    va_start(arglist, format);
    
    // length with '\0'
    int length = 1 + vsnprintf(NULL, 0, format, arglist);

    char *buffer = CUTILS_STRINGUTILS_ALLOCATOR( length * sizeof(char)); 
    vsnprintf(buffer, length, format, arglist);
    va_end(arglist);

    return buffer;
}

#include "utils/stringBuilder.c"

#endif // CUTILS_STRINGUTILS_IMPL