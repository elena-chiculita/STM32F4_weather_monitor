#include "list_test.h"
#include "alloc.h"
#include "util.h"


uint32_t list_test(void)
{
    list_t list;
    list_elem_t *new[LIST_TEST_ELEM_NO], *elem;
    uint8_t list_test_val[LIST_TEST_ELEM_NO] = {100, 50, 80, 100, 200, 150};
    uint8_t list_test_val_ord[LIST_TEST_ELEM_NO] = {50, 80, 100, 100, 150, 200};
    uint8_t list_test_val_parse[LIST_TEST_ELEM_NO] = {0, 30, 50, 50, 100, 150};
    uint8_t list_test_find_values[LIST_TEST_ELEM_NO] = {100, 150, 80, 200, 50, 123};
    uint8_t list_test_find_no[LIST_TEST_ELEM_NO] = {2, 1, 1, 1, 1, 0};
    uint8_t list_test_find_values_index[LIST_TEST_ELEM_NO] = {0, 3, 5, 2, 4, 1};
    uint8_t i, j, n, val;

    list_init(&list);

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        new[i] = calloc(1, sizeof(list_test_t));
        ((list_test_t *)new[i])->val = list_test_val[i];
        list_add_last(&list, new[i]);
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        elem = list_get_first(&list);
        TEST(elem == new[i])
        elem = list_remove_first(&list);
        TEST(elem == new[i])

        if (i == (LIST_TEST_ELEM_NO - 1))
        {
            TEST(list_is_empty(&list) == TRUE)
        }
        else
        {
            TEST(list_is_empty(&list) == FALSE)
        }
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        list_add_ordered(&list, new[i], list_test_find_pos);
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        elem = list_get_first(&list);
        TEST(((list_test_t *)elem)->val == list_test_val_ord[i])
        elem = list_remove_first(&list);
        TEST(((list_test_t *)elem)->val == list_test_val_ord[i])

        if (i == (LIST_TEST_ELEM_NO - 1))
        {
            TEST(list_is_empty(&list) == TRUE)
        }
        else
        {
            TEST(list_is_empty(&list) == FALSE)
        }
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        list_add_ordered(&list, new[i], list_test_find_pos);
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        elem = list_get_elem(&list, list_test_find_val, &list_test_val_ord[i]);
        TEST(((list_test_t *)elem)->val == list_test_val_ord[i])
        list_remove(&list, elem);
        TEST(((list_test_t *)elem)->val == list_test_val_ord[i])

        if (i == (LIST_TEST_ELEM_NO - 1))
        {
            TEST(list_is_empty(&list) == TRUE)
        }
        else
        {
            TEST(list_is_empty(&list) == FALSE)
        }
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        list_add_last(&list, new[i]);
    }

    for (i = 0, j = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        n = 0;
        elem = NULL;

        do
        {
            elem = list_get_elems(&list, elem, list_test_find_val, &list_test_find_values[i]);
            if (elem == NULL)
            {
                TEST(n == list_test_find_no[i]);
                break;
            }
            else
            {
                TEST((((list_test_t *)elem)->val == list_test_find_values[i]) && (elem == new[list_test_find_values_index[j]]))
                list_remove(&list, elem);
                TEST((((list_test_t *)elem)->val == list_test_find_values[i]) && (elem == new[list_test_find_values_index[j]]))
                j++;
                n++;
            }
        } while (elem);

        if (i >= (LIST_TEST_ELEM_NO - 2))
        {
            TEST(list_is_empty(&list) == TRUE)
        }
        else
        {
            TEST(list_is_empty(&list) == FALSE)
        }
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        list_add_ordered(&list, new[i], list_test_find_pos);
    }

    val = 50;
    list_parse(&list, list_test_update, &val);

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        elem = list_get_first(&list);
        TEST(((list_test_t *)elem)->val == list_test_val_parse[i])
        elem = list_remove_first(&list);
        TEST(((list_test_t *)elem)->val == list_test_val_parse[i])

        if (i == (LIST_TEST_ELEM_NO - 1))
        {
            TEST(list_is_empty(&list) == TRUE)
        }
        else
        {
            TEST(list_is_empty(&list) == FALSE)
        }
    }

    for (i = 0; i < LIST_TEST_ELEM_NO; i++)
    {
        free(new[i]);
    }

    return 0;
}

bool list_test_find_val(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    if (((list_test_t *)elem)->val == *(uint8_t *)arg)
    {
        return TRUE;
    }

    return FALSE;
}

int list_test_find_pos(list_elem_t *elem, list_elem_t *new)
{
    ASSERT((elem != NULL) && (new != NULL));

    if (((list_test_t *)elem)->val < ((list_test_t *)new)->val)
    {
        return -1;
    }
    else if (((list_test_t *)elem)->val > ((list_test_t *)new)->val)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void list_test_update(list_elem_t *elem, void *arg)
{
    ASSERT((elem != NULL) && (arg != NULL));

    ((list_test_t *)elem)->val -= *((uint8_t *)arg);
}
