#ifndef _LIST_H_
#define _LIST_H_

#include "embedded_types.h"


typedef struct list_elem_tag
{
    struct list_elem_tag *next;
} list_elem_t;

typedef struct list_tag
{
    list_elem_t *head;
} list_t;

void list_init(list_t *list);
bool list_is_empty(list_t *list);
void list_add_last(list_t *list, list_elem_t *elem);
list_elem_t* list_remove_first(list_t *list);

#endif /* _LIST_H_ */

