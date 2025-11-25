#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(Dlist *list, void (*destroy)(void *data)) {

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;

}

void dlist_destroy(Dlist *list) {

    void *data;

    while (dlist_size(list) > 0) {

        if (dlist_remove(list, dlist_head(list), &data) == 0 && list->destroy != NULL)
            list->destroy(data);   

    }

    memset(list, 0, sizeof(Dlist));

    return;

}

int list_ins_next(Dlist *list, DListElmt *element, const void *data) {

    DListElmt *new_element;

    /* Numa List, element NULL fazia inserir na cabeça. Aqui só é permitido
       NULL se a lista estiver vazia. Caso a lista não seja vazia, se quiser 
       inserir na cabeça use list_ins_prev e use list->head como element
    */

    if (element == NULL && list->size !=0)
        return -1;

    if ((new_element = malloc(sizeof(DListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;

    if (dlist_size(list) == 0) {

        new_element->prev = NULL;
        new_element->next = NULL;
        list->head = new_element;
        list->tail = new_element;

    } else {

        new_element->prev = element;
        new_element->next = element->next;

        if (element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;

        element->next = new_element;

    }

    ++(list->size);

    return 0;

}

int list_ins_prev(Dlist *list, DListElmt *element, const void *data) {

    DListElmt *new_element;

    /* Numa List, element NULL fazia inserir na cabeça. Aqui só é permitido
       NULL se a lista estiver vazia. Caso a lista não seja vazia, se quiser 
       inserir na cauda use list_ins_next e use list->tail como element
    */

    if (element == NULL && list->size !=0)
        return -1;

    if ((new_element = malloc(sizeof(DListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;

    if (dlist_size(list) == 0) {

        new_element->prev = NULL;
        new_element->next = NULL;
        list->head = new_element;
        list->tail = new_element;

    } else {

        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;

    }

    ++(list->size);

    return 0;

}



