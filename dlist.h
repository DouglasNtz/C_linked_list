#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct DListElmt_
{
    void *data;
    struct DListElmt_ *prev;
    struct DListElmt_ *next;   
} DListElmt;

typedef struct DList_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    DListElmt *head;
    DListElmt *tail;
} Dlist;

void dlist_init(Dlist *list, void (*destroy)(void *data));

void dlist_destroy(Dlist *list);

int dlist_ins_next(Dlist *list, DListElmt *element, const void *data);

int dlist_ins_prev(Dlist *list, DListElmt *element, const void *data);

int dlist_remove(Dlist *list, DListElmt *element, void **data);

static inline int dlist_size(Dlist *list) {
    return list->size;
}

static inline DListElmt *dlist_head(Dlist *list) {
    return list->head;
}

static inline DListElmt *dlist_tail(Dlist *list) {
    return list->tail;
}

static inline int dlist_is_head(DListElmt *element) {
    return element->prev == NULL ? 1 : 0;
}

static inline int dlist_is_tail(DListElmt *element) {
    return element->next == NULL ? 1 : 0;
}

static inline void *dlist_data(DListElmt *element) {
    return element->data;
}

static inline DListElmt *dlist_next(DListElmt *element) {
    return element->next;
}

static inline DListElmt *dlist_prev(DListElmt *element) {
    return element->prev;
}

#endif