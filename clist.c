#include <stdlib.h>
#include <string.h>

#include "clist.h"

void clist_init(CList *list, void (*destroy)(void *data)) {

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    
    return;

}

void clist_destroy(CList *list) {

    void *data;

    while (clist_size(list) > 0) {

        /* Quando a lista tiver um único elemento, ele será também o último e seu next será ele mesmo */

        if(clist_rem_next(list, list->head, &data) == 0 && list->destroy != NULL) 
            list->destroy(data);

    }

    memset(list, 0, sizeof(CList));

    return;
}

int clist_ins_next(CList *list, CListElmt *element, const void *data) {

    /* Neste caso, se já existe cabeça, nunca podemos inserir antes da cabeça.
       Pois se quiséssemos aplicar a lógica de passar NULL para inserir antes da cabeça,
       seria difícil saber qual quem é o último elemento para mudar seu next para new_element.
    */

    CListElmt *new_element;

    if (element == NULL && clist_size(list) != 0)
        return -1;

    if ((new_element = malloc(sizeof(CListElmt))) == NULL)
        return -1;

    new_element->data = (void *)data;

    if (clist_size(list) == 0) {

        list->head = new_element;
        new_element->next = new_element;
    
    } else {

        new_element->next = element->next;
        element->next = new_element;        

    }

    ++(list->size);

    return 0;
}

int clist_rem_next(CList *list, CListElmt *element, void **data) {

    CListElmt *old_element;

    if (element == NULL || clist_size(list) == 0)
        return -1;

    *data = element->next->data;
    old_element = element->next;

    if (element->next == element)  /* Só tem cabeça a lista */

        list->head = NULL;

    else {  /* Mais de um elemento */

        element->next = old_element->next;

        if (old_element == list->head)
            list->head = old_element->next;

    }

    free(old_element);

    --(list->size);

    return 0;
}