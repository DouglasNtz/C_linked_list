#include "clist.h"
#include "page.h"

int replace_page(CListElmt **current) {  /* retorna o número da página a ser substituída */

    while (((Page *)(*current)->data)->reference != 0) {
        ((Page *)(*current)->data)->reference = 0;
        *current = (*current)->next;
    }

    return ((Page *)(*current)->data)->number;

}