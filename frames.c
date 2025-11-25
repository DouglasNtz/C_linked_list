#include <stdlib.h>

#include "frames.h"
#include "list.h"

int alloc_frame(List *frames) {

    int frame_number;
    int *data;

    if (list_size(frames) == 0)  /* Sem frames disponíveis */
        return -1;  

    else {

        list_rem_next(frames, NULL, (void **)&data);  /* Exclui a cabeça da lista */

        frame_number = *data;  /* data tem o mesmo valor (endereço apontado) do ponteiro data da cabeça excluída */
        free(data);  /* A regra aqui é que cada elemento da lista tem o ponteiro data com memória alocada via malloc */
    
    }

    return frame_number;
}

int free_frame(List *frames, int frame_number) {

    int *data;

    if ((data = (int *)malloc(sizeof(int))) == NULL) 
        return -1;

    *data = frame_number;

    if (list_ins_next(frames, NULL, data) != 0)  /* pode falhar se não conseguirmos memória pra criar elemento novo */
        return -1;

    return 0;

}