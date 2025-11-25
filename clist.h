#ifndef CLIST_H
#define CLIST_H

#include <stddef.h>

typedef struct CListElmt_
{
    void *data;
    struct CListElmt_ *next;
} CListElmt;

typedef struct Clist_ 
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    CListElmt *head;
} CList;

void clist_init(CList *list, void (*destroy)(void *data));

void clist_destroy(CList *list);

int clist_ins_next(CList *list, CListElmt *element, const void *data);

int clist_rem_next(CList *list, CListElmt *element, void **data);

static inline int clist_size(CList *list) {
    return list->size;
}

static inline CListElmt *clist_head(CList *list) {
    return list->head;
}

static inline void *clist_data(CListElmt *element) {
    return element->data;
}

static inline CListElmt *clist_next(CListElmt *element) {
    return element->next;
}

#endif