#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/* 
Define struct que representa um elemento da linked list.
Cada elemento contém:
1. Um ponteiro genérico chamado data que aponta para o dado em si.
2. Um ponteiro chamado next que aponta para o próximo elemento da lista.  
*/

typedef struct ListElmt_
{
    void *data;
    struct ListElmt_ *next;    
} ListElmt;

/*
Define a struct que representa a linked list.
Cada lista contém:
1. Informação do seu número de elementos no campo size.
2. Um ponteiro para uma função de comparação entre elementos.
3. Um ponteiro para um função que libera memória ao destruir a lista.
4. Um ponteiro para o primeiro elemento.
5. Um ponteiro para o último elemento.
*/

typedef struct List_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
} List;

/*
Função que inicia uma lista. Basta fornecer um ponteiro List e uma função para destruir a lista
quando list_destroy for chamada.
*/

void list_init(List *list, void (*destroy)(void *data));

/*
Função que destrói a lista e cada um de seus elementos. Chama destroy para cada um dos elementos.
*/

void list_destroy(List *list);

/*
Insere um elemento (data) após elment na lista list. Se element for NULL, insere na cabeça.
*/

int list_ins_next(List *list, ListElmt *element, const void *data);

/*
Remove o element que vem depois de element. Se element for NULL, remove a cabeça.
Além disso atribui o ponteiro void data do elemento para um ponteiro void p 
que passamos como &p para função.
*/

int list_rem_next(List *list, ListElmt *element, void **data);

/*
Retorna o tamanho da lista, ou seja, o campo size da lista.
*/

static inline int list_size(const List *list) {
    return list->size;
}

/*
Retorna o ponteiro para o elemento head, ou seja, o campo head da lista.
*/

static inline ListElmt *list_head(const List *list) {
    return list->head;
}

/*
Retorna o ponteiro para o elemento tail, ou seja, o campo tail da lista.
*/

static inline ListElmt *list_tail(const List *list) {
    return list->tail;
}

/*
Retorna 1 se o elemento é a cabeça da lista e 0 se não for.
Veja que comparamos os valores dos ponteiros (os endereços apontados), 
e não os valores dos endereços apontados (pois isso é mais fraco).
Para umn elemento ser cabeça, ele precisa ocupar o mesmo espaço de memória apontado 
pelo campo head da lista (valor do campo head, que é um ponteiro). 
*/

static inline int list_is_head(const List *list, const ListElmt *element) {
    return (list->head == element)? 1 : 0;
}

/*
Retorna 1 se o elemento é a cauda e 0 se não for.
Aqui não precisamos da lista
*/

static inline int list_is_tail(const ListElmt *element) {
    return (element->next == NULL)? 1 : 0;
}

/*
Retorna os dados de um elemento. Um ponteiro, tal como o campo data do elemento.
*/

static inline void *list_data(const ListElmt *element) {
    return element->data;
}

/*
Retorna o próximo elemento de um elemento. Um ponteiro, tal como no campo next do elemento.
*/

static inline ListElmt *list_next(const ListElmt *element) {
    return element->next;
}

#endif

