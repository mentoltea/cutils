#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

size_t malloc_calls = 0;
void* test_malloc( size_t size ) {
    malloc_calls++;
    return malloc(size);
}
#define CUTILS_STRINGUTILS_ALLOCATOR test_malloc

size_t free_calls = 0;
void test_free( void *ptr ) {
    free_calls++;
    return free( ptr );
}
#define CUTILS_STRINGUTILS_DEALLOCATOR test_free

size_t memcpy_calls = 0;
void* test_memcpy( void* dest, const void* src, size_t count ) {
    memcpy_calls++;
    return memcpy(dest, src, count);
}
#define CUTILS_STRINGUTILS_MEMCPY test_memcpy

void print_callinfo() {
    printf("Malloc: %lld\n", malloc_calls);
    printf("Free: %lld\n", free_calls);
    printf("Memcpy: %lld\n", memcpy_calls);
}