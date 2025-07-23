#include "stringBuilder.h"

void sb_append(StringBuilder *sb, char* string) {
    ll_append_back(*sb, StringChunk, temp_sprintf(string));
    sb->last->length = strlen(sb->last->item);
}

void sb_appends(StringBuilder *sb, char* string, size_t length) {
    ll_append_back(*sb, StringChunk, make_terminated(string, length));
    sb->last->length = strlen(sb->last->item);
}

void sb_appendf(StringBuilder *sb, char* format, ...) {
    va_list arglist;
    va_start(arglist, format);
    
    // length with '\0'
    int length = 1 + vsnprintf(NULL, 0, format, arglist);
    
    char *buffer = CUTILS_STRINGUTILS_ALLOCATOR( length * sizeof(char)); 
    vsnprintf(buffer, length, format, arglist);
    va_end(arglist);
    
    ll_append_back(*sb, StringChunk, buffer);
    sb->last->length = length-1;
}

void sb_free(StringBuilder *sb) {
    ll_foreach(StringChunk, ptr, *sb) {
        CUTILS_STRINGUTILS_DEALLOCATOR( ptr->item );
    }
    ll_free( *sb );
}

size_t sb_length(StringBuilder *sb) {
    size_t full_length = 0;
    ll_foreach(StringChunk, ptr, *sb) {
        full_length += ptr->length;
    }
    return full_length;
}

char* sb_make_string(StringBuilder *sb) {
    size_t length = sb_length(sb);
    char* string = CUTILS_STRINGUTILS_ALLOCATOR( (length+1) * sizeof(char));
    char* curr_buffer = string;
    
    ll_foreach(StringChunk, ptr, *sb) {
        CUTILS_STRINGUTILS_MEMCPY(curr_buffer, ptr->item, ptr->length*sizeof(char));
        curr_buffer += ptr->length;
    }
    string[length] = '\0';
    sb_free(sb);
    return string;
}

char* sb_make_string_nofree(StringBuilder *sb) {
    size_t length = sb_length(sb);
    char* string = CUTILS_STRINGUTILS_ALLOCATOR( (length+1) * sizeof(char));
    char* curr_buffer = string;
    
    ll_foreach(StringChunk, ptr, *sb) {
        CUTILS_STRINGUTILS_MEMCPY(curr_buffer, ptr->item, ptr->length*sizeof(char));
        curr_buffer += ptr->length;
    }
    string[length] = '\0';
    return string;
}