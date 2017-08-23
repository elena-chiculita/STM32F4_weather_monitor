#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "embedded_types.h"
#include <stddef.h>


typedef enum sem_type_tag
{
    SEM_TYPE_BINARY = 0,
    SEM_TYPE_COUNTING = 1
} sem_type_t;

typedef struct sem_tag
{
    size_t count;
    sem_type_t type;
} sem_t, *sem_handle_t;


sem_handle_t sem_init(sem_type_t type, size_t initial_count);
void sem_take(sem_handle_t sem);
void sem_give(sem_handle_t sem);
void sem_destroy(sem_handle_t sem);

#endif /* _SEMAPHORE_H_ */
