#include "semaphore.h"
#include "alloc.h"
#include "util.h"


sem_handle_t sem_init(sem_type_t type, size_t initial_count)
{
    sem_handle_t sem;

    sem = malloc(sizeof(sem_t));
    ASSERT(sem != NULL);
    sem->count = initial_count;
    sem->type = type;

    return sem;
}

void sem_take(sem_handle_t sem)
{
    while (sem->count == 0);

    /* disable interrupts */
    _disable_irq();

    sem->count--;

    /* enable interrupts */
    _enable_irq();
}

void sem_give(sem_handle_t sem)
{
    /* disable interrupts */
    _disable_irq();

    if (((sem->type == SEM_TYPE_BINARY) && (sem->count == 0)) || (sem->type == SEM_TYPE_COUNTING))
    {
        sem->count++;
    }

    /* enable interrupts */
    _enable_irq();
}

void sem_destroy(sem_handle_t sem)
{
    ASSERT(sem != NULL);
    free((void *)sem);
}
