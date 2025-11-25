#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data)) {

    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    
    return;

}

void list_destroy(List *list) {

    void *data;

    while (list_size(list) > 0) {

        if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL) {
            list->destroy(data); /* função que sabe destruir por completo o dado apontado por element->data */
        }
    }

    memset(list, 0, sizeof(List));  /* reseta os bytes ocupados pela lista */

    return;

}

int list_ins_next(List *list, ListElmt *element, const void *data) {

    ListElmt *new_element;  /* Cria um ponteiro para elemento */

    if ((new_element = malloc(sizeof(ListElmt))) == NULL)  /* aloca espaço na memória para o elemento */
        return -1;

    new_element->data = (void *)data;  /* copia o ponteiro de dados para o campo ponteiro de dados do elemento.
                                          O cast é para transformar const void* em void * */


    if (element == NULL) {   /* Se element é NULL, vamos inserir na cabeça */

        if(list_size(list) == 0)   /* Se a lista é vazia, o elemeno novo será cabeça e cauda */
            list->tail = new_element;

        new_element->next = list->head;  /* elemento novo tem seu campo next apontando para a cabeça antiga */
        list->head = new_element; /* a cabeça da lista é atualizada para o elemento novo */

    } else {  /* vamos inserir depois de element (elemento de fato)*/

        if(element->next == NULL)  /* se element é cauda, então o elemento novo será a nova cauda */
            list->tail = new_element;

            new_element->next = element->next; /* O next de new_element é o antigo next de element*/
            element->next = new_element; /* new_element é o novo next de element */

    }

    ++(list->size);  /* Aumenta 1 elemento no tamanho da lista */

    return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {

    ListElmt *old_element;

    if (list_size(list) == 0) /* Não há o que excluir */
        return -1;

    if (element == NULL) {   /* Vamos remover a cabeça */
        
        old_element = list->head;  /* elemento a ser excluído é atribuído a old_element */
        *data = old_element->data;  /* data vai apontar para o ponteiro data de old_element */
        list->head = old_element->next; /* atualizamos a nova cabeça da lista, que pode inclusive ser NULL */

        if (list_size(list) == 1)  /* tamanho da lista antes da exclusão */
            list->tail = NULL;  /* se só tinhamos 1 elemento, ficaremos com nenhum */
    
    } else {

        if (element->next == NULL)  /* aqui não há o que excluir, pois element é cauda */
            return -1;

        old_element = element->next; /* elemento a ser excluído é atribuído a old_element */
        *data = old_element->data; /* data vai apontar para o ponteiro data de old_element */
        element->next = old_element->next;  /* atualizamos o next de element para o depois do excluído */

        if (element->next == NULL)  /* aqui element->next já está atualizado */
            list->tail = element;   /* se excluímos o último, então element é a nova cauda */

    }

    free(old_element); /* libera a memória apontada pelo ponteiro old_element, que seria a struct 
                          Mas isso não mexe nos dados antes apontados por old_element->data */

    --(list->size); /* Diminui em 1 elemento o tamanho da lista */

    return 0;

}