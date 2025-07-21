#ifndef CUTILS_LIST
#define CUTILS_LIST

/*

Default node struct:
Node {
    Node* prev;
    Node* next;    
    T item;
}

List {
    Node* first;
    Node* last;
    size_t count;
}

*/

#ifndef CUTILS_LIST_ALLOCATOR
#include <stdlib.h>
// void* malloc( size_t size );
#define CUTILS_LIST_ALLOCATOR malloc
#endif

#ifndef CUTILS_LIST_DEALLOCATOR
#include <stdlib.h>
// void free( void *ptr );
#define CUTILS_LIST_DEALLOCATOR free
#endif

#ifndef CUTILS_LIST_MEMCPY
#include <string.h>
// void* memcpy( void* dest, const void* src, std::size_t count );
#define CUTILS_LIST_MEMCPY memcpy
#endif

#define ll_node_free(nodeptr) {         \
    CUTILS_LIST_DEALLOCATOR((nodeptr));   \
}

#define ll_node_free_recursive(nodeptr) {       \
    while ((nodeptr)->next) {                     \
        (nodeptr) = (nodeptr)->next;                \
        ll_node_free((nodeptr)->prev);            \
    }                                           \
    ll_node_free((nodeptr));                      \
}

#define ll_free(ll) {                       \
    if ((ll).first) {                         \
        ll_node_free_recursive((ll).first);   \
        (ll).first = NULL;                    \
        (ll).last = NULL;                     \
        (ll).count = 0;                       \
    }                                       \
}

#define ll_append_back(ll, NodeType, value) { \
    NodeType * _newnode = CUTILS_LIST_ALLOCATOR( sizeof(NodeType) ); \
    _newnode->prev = NULL; \
    _newnode->next = NULL; \
    _newnode->item = (value); \
    if (! (ll).last) { \
        (ll).first = _newnode; \
        (ll).last = _newnode; \
        (ll).count = 1; \
    } else { \
        (ll).last->next = _newnode; \
        _newnode->prev = (ll).last; \
        (ll).last = _newnode; \
        (ll).count += 1; \
    } \
}

#define ll_append_front(ll, NodeType, value) { \
    NodeType * _newnode = CUTILS_LIST_ALLOCATOR( sizeof(NodeType) ); \
    _newnode->prev = NULL; \
    _newnode->next = NULL; \
    _newnode->item = (value); \
    if (! (ll).first) { \
        (ll).first = _newnode; \
        (ll).last = _newnode; \
        (ll).count = 1; \
    } else { \
        (ll).first->prev = _newnode; \
        _newnode->next = (ll).first; \
        (ll).first = _newnode; \
        (ll).count += 1; \
    } \
}

#define ll_copy(NodeType, ll_to, ll_from) { \
    ll_free( (ll_to) ); \
    ll_foreach( NodeType, _copy_ptr, (ll_from) ) { \
        ll_append_back( (ll_to), NodeType, _copy_ptr->item); \
    } \
}

#define ll_concat_raw(ll1, ll2) { \
    (ll1).last->next = (ll2).first; \
    (ll2).first->prev = (ll1).last; \
    (ll1).last = (ll2).last; \
    (ll2).first = (ll1).first; \
    (ll1).count += (ll2).count; \
    (ll2).count = (ll1).count; \
}

#define ll_concat(ListType, NodeType, ll1, ll2) { \
    ListType _ll2_copy = {0}; \
    ll_copy(NodeType, _ll2_copy, (ll2)); \
    ll_concat_raw((ll1), _ll2_copy); \
}

#define ll_foreach(T, it, ll) for (T* it = (ll).first; it != NULL; it = it->next)

#define ll_reverse(NodeType, ll) { \
    void* _reverse_temp; \
    for (NodeType* _reverse_ptr = (ll).first; _reverse_ptr != NULL; ) { \
        _reverse_temp = (void*) _reverse_ptr->next; \
        _reverse_ptr->next = _reverse_ptr->prev; \
        _reverse_ptr->prev = (NodeType*) _reverse_temp; \
        _reverse_ptr = (NodeType*) _reverse_temp; \
    } \
    _reverse_temp = (ll).first; \
    (ll).first = (ll).last; \
    (ll).last = _reverse_temp; \
}

#define ll_pop(NodeType, ll, index) { \
    NodeType* _pop_ptr; \
    if ((index) < (ll).count/2) { \
        _pop_ptr = (ll).first; \
        size_t _cur_idx = 0; \
        while (_cur_idx < index) { \
            _pop_ptr = _pop_ptr->next; \
            _cur_idx++; \
        } \
    } else { \
        _pop_ptr = (ll).last; \
        size_t _cur_idx = (ll).count - 1; \
        while (_cur_idx > index) { \
            _pop_ptr = _pop_ptr->prev; \
            _cur_idx--; \
        } \
    } \
    if (_pop_ptr->prev) _pop_ptr->prev->next = _pop_ptr->next; \
    if (_pop_ptr->next) _pop_ptr->next->prev = _pop_ptr->prev; \
    if (_pop_ptr == (ll).first) \
        (ll).first = _pop_ptr->prev ? _pop_ptr->prev : _pop_ptr->next; \
    if (_pop_ptr == (ll).last) \
        (ll).last = _pop_ptr->next ? _pop_ptr->next : _pop_ptr->prev; \
    ll_node_free(_pop_ptr); \
}

#endif // CUTILS_LIST