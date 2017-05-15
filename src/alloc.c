#include "alloc.h"
#include "util.h"


__attribute__((section (".heap"))) pool_t pool;


void alloc_init(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_4_BLOCKS; i++)
    {
        pool.pool_4[i].free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_8_BLOCKS; i++)
    {
        pool.pool_8[i].free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_16_BLOCKS; i++)
    {
        pool.pool_16[i].free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_32_BLOCKS; i++)
    {
        pool.pool_32[i].free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_64_BLOCKS; i++)
    {
        pool.pool_64[i].free = TRUE;
    }
}

void* alloc_get_pool_4_free_block(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_4_BLOCKS; i++)
    {
        if (pool.pool_4[i].free)
        {
            pool.pool_4[i].free = FALSE;
            return (void *)&(pool.pool_4[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_8_free_block(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_8_BLOCKS; i++)
    {
        if (pool.pool_8[i].free)
        {
            pool.pool_8[i].free = FALSE;
            return (void *)&(pool.pool_8[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_16_free_block(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_16_BLOCKS; i++)
    {
        if (pool.pool_16[i].free)
        {
            pool.pool_16[i].free = FALSE;
            return (void *)&(pool.pool_16[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_32_free_block(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_32_BLOCKS; i++)
    {
        if (pool.pool_32[i].free)
        {
            pool.pool_32[i].free = FALSE;
            return (void *)&(pool.pool_32[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_64_free_block(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_64_BLOCKS; i++)
    {
        if (pool.pool_64[i].free)
        {
            pool.pool_64[i].free = FALSE;
            return (void *)&(pool.pool_64[i].data);
        }
    }

    return NULL;
}

void* malloc(size_t size)
{
    void *address = NULL;

    /* disable interrupts */
    _disable_irq();

    if ((size > 0) && (size <= 4))
    {
        address = alloc_get_pool_4_free_block();
    }
    else if (size <= 8)
    {
        address = alloc_get_pool_8_free_block();
    }
    else if (size <= 16)
    {
        address = alloc_get_pool_16_free_block();
    }
    else if (size <= 32)
    {
        address = alloc_get_pool_32_free_block();
    }
    else if (size <= 64)
    {
        address = alloc_get_pool_64_free_block();
    }

    /* enable interrupts */
    _enable_irq();

    ASSERT(address != NULL);
    
    return address;
}

void* calloc(size_t num, size_t size)
{
    void *address;

    address = malloc(num * size);
    ASSERT(address != NULL);
    memset(address, 0, size);

    return address;
}

void free(void *ptr)
{
    /* disable interrupts */
    _disable_irq();
    ((pool_4_block_t *)((uint8_t *)ptr - FIELD_OFFSET(pool_4_block_t, free)))->free = TRUE;
    /* enable interrupts */
    _enable_irq();
}
