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

typedef int (*list_find_pos_elem_t)(list_elem_t*, list_elem_t*);
typedef bool (*list_find_elem_t)(list_elem_t*, void*);
typedef void (*list_update)(list_elem_t*, void*);


void list_init(list_t *list);
bool list_is_empty(list_t *list);
void list_add_last(list_t *list, list_elem_t *elem);
void list_add_ordered(list_t *list, list_elem_t *elem, list_find_pos_elem_t fn);
list_elem_t* list_remove_first(list_t *list);
void list_remove(list_t *list, list_elem_t *elem);
list_elem_t* list_get_first(list_t *list);
list_elem_t* list_get_next_elem(list_elem_t *elem);
list_elem_t* list_get_elem(list_t *list, list_find_elem_t fn, void *arg);
list_elem_t* list_get_elems(list_t *list, list_elem_t *elem, list_find_elem_t fn, void *arg);
void list_parse(list_t *list, list_update fn, void *arg);

#endif /* _LIST_H_ */
