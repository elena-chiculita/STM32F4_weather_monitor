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
    ASSERT((list != NULL) && (elem != NULL));

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

void list_add_ordered(list_t *list, list_elem_t *elem, list_find_pos_elem_t fn)
{
    list_elem_t *p, *tmp;

    ASSERT((list != NULL) && (elem != NULL) && (fn != NULL));

    if (list->head == NULL)
    {
        list->head = elem;
        list->head->next = NULL;
    }
    else if (fn(list->head, elem) > 0)
    {
        tmp = list->head;
        list->head = elem;
        list->head->next = tmp;
    }
    else
    {
        p = list->head;

        while (p->next)
        {
            if (fn(p->next, elem) > 0)
            {
                tmp = p->next;
                p->next = elem;
                elem->next = tmp;

                return;
            }

            p = p->next;
        }

        p->next = elem;
        elem->next = NULL;
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

void list_remove(list_t *list, list_elem_t *elem)
{
    list_elem_t *aux;

    ASSERT((list != NULL) && (elem != NULL));

    if (list->head == NULL)
    {
        return;
    }

    if (list->head == elem)
    {
        list->head = list->head->next;
        return;
    }

    aux = list->head;

    while (aux->next)
    {
        if (aux->next == elem)
        {
            aux->next = aux->next->next;
            break;
        }

        aux = aux->next;
    }
}

list_elem_t* list_get_first(list_t *list)
{
    ASSERT(list != NULL);

    return list->head;
}

list_elem_t* list_get_next_elem(list_elem_t *elem)
{
    if (elem != NULL)
    {
        return elem->next;
    }

    return NULL;
}

list_elem_t* list_get_elem(list_t *list, list_find_elem_t fn, void *arg)
{
    list_elem_t *p;

    ASSERT((list != NULL) && (fn != NULL) && (arg != NULL));

    p = list->head;

    while (p)
    {
        if (fn(p, arg))
        {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

list_elem_t* list_get_elems(list_t *list, list_elem_t *elem, list_find_elem_t fn, void *arg)
{
    list_elem_t *p;

    ASSERT((list != NULL) && (fn != NULL) && (arg != NULL));

    if (elem == NULL)
    {
        p = list->head;
    }
    else
    {
        p = elem->next;
    }

    while (p)
    {
        if (fn(p, arg))
        {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

void list_parse(list_t *list, list_update fn, void *arg)
{
    list_elem_t *p;

    ASSERT((list != NULL) && (fn != NULL) && (arg != NULL));

    p = list->head;

    while (p)
    {
        fn(p, arg);
        p = p->next;
    }
}
