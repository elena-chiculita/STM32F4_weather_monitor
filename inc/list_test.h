#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include "test.h"
#include "list.h"


#define LIST_TEST_ELEM_NO 6


typedef struct list_test_tag
{
    list_elem_t elem;
    uint32_t val;
} list_test_t;


uint32_t list_test(void);
bool list_test_find_val(list_elem_t *elem, void *arg);
int list_test_find_pos(list_elem_t *elem, list_elem_t *new);
void list_test_update(list_elem_t *elem, void *val);

#endif /* _LIST_TEST_H_ */
