#include "list.h"
#include "alloc.h"
#include "util.h"


void list_init(list_t *list)
{
    ASSERT(list != NULL);

    list->head = NULL;
}

bool list_is_empty(list_t *list)
{
    ASSERT(list != NULL);

    if (list->head == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void list_add_last(list_t *list, list_elem_t *elem)
{
    ASSERT(list != NULL);
    ASSERT(elem != NULL);

    if (list->head == NULL)
    {
        list->head = elem;
        list->head->next = NULL;
    }
    else
    {
        list_elem_t *p = list->head;

        while (p->next)
        {
            p = p->next;
        }
        p->next = elem;
        p->next->next = NULL;
    }
}

list_elem_t* list_remove_first(list_t *list)
{
    list_elem_t *aux;

    ASSERT(list != NULL);

    aux = list->head;
    if (list->head != NULL)
    {
        list->head = list->head->next;
    }

    return aux;
}
