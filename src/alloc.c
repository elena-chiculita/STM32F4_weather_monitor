#include "alloc.h"
#include "irq.h"
#include "lib.h"
#include "util.h"


__attribute__((section (".heap"))) pool_t pool;


void alloc_init(void)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_4_BLOCKS; i++)
    {
        pool.pool_4[i].header.lr = 0;
        pool.pool_4[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_8_BLOCKS; i++)
    {
        pool.pool_8[i].header.lr = 0;
        pool.pool_8[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_16_BLOCKS; i++)
    {
        pool.pool_16[i].header.lr = 0;
        pool.pool_16[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_32_BLOCKS; i++)
    {
        pool.pool_32[i].header.lr = 0;
        pool.pool_32[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_64_BLOCKS; i++)
    {
        pool.pool_64[i].header.lr = 0;
        pool.pool_64[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_128_BLOCKS; i++)
    {
        pool.pool_128[i].header.lr = 0;
        pool.pool_128[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_256_BLOCKS; i++)
    {
        pool.pool_256[i].header.lr = 0;
        pool.pool_256[i].header.free = TRUE;
    }
    for (i = 0; i < ALLOC_POOL_512_BLOCKS; i++)
    {
        pool.pool_512[i].header.lr = 0;
        pool.pool_512[i].header.free = TRUE;
    }
}

void* alloc_get_pool_4_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_4_BLOCKS; i++)
    {
        if (pool.pool_4[i].header.free)
        {
            pool.pool_4[i].header.lr = lr;
            pool.pool_4[i].header.free = FALSE;
            return (void *)&(pool.pool_4[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_8_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_8_BLOCKS; i++)
    {
        if (pool.pool_8[i].header.free)
        {
            pool.pool_8[i].header.lr = lr;
            pool.pool_8[i].header.free = FALSE;
            return (void *)&(pool.pool_8[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_16_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_16_BLOCKS; i++)
    {
        if (pool.pool_16[i].header.free)
        {
            pool.pool_16[i].header.lr = lr;
            pool.pool_16[i].header.free = FALSE;
            return (void *)&(pool.pool_16[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_32_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_32_BLOCKS; i++)
    {
        if (pool.pool_32[i].header.free)
        {
            pool.pool_32[i].header.lr = lr;
            pool.pool_32[i].header.free = FALSE;
            return (void *)&(pool.pool_32[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_64_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_64_BLOCKS; i++)
    {
        if (pool.pool_64[i].header.free)
        {
            pool.pool_64[i].header.lr = lr;
            pool.pool_64[i].header.free = FALSE;
            return (void *)&(pool.pool_64[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_128_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_128_BLOCKS; i++)
    {
        if (pool.pool_128[i].header.free)
        {
            pool.pool_128[i].header.lr = lr;
            pool.pool_128[i].header.free = FALSE;
            return (void *)&(pool.pool_128[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_256_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_256_BLOCKS; i++)
    {
        if (pool.pool_256[i].header.free)
        {
            pool.pool_256[i].header.lr = lr;
            pool.pool_256[i].header.free = FALSE;
            return (void *)&(pool.pool_256[i].data);
        }
    }

    return NULL;
}

void* alloc_get_pool_512_free_block(size_t lr)
{
    size_t i;

    for (i = 0; i < ALLOC_POOL_512_BLOCKS; i++)
    {
        if (pool.pool_512[i].header.free)
        {
            pool.pool_512[i].header.lr = lr;
            pool.pool_512[i].header.free = FALSE;
            return (void *)&(pool.pool_512[i].data);
        }
    }

    return NULL;
}

void* _malloc(size_t size, size_t lr)
{
    void *address = NULL;

    /* disable interrupts */
    _disable_irq();

    if ((size > 0) && (size <= 4))
    {
        address = alloc_get_pool_4_free_block(lr);
    }
    else if (size <= 8)
    {
        address = alloc_get_pool_8_free_block(lr);
    }
    else if (size <= 16)
    {
        address = alloc_get_pool_16_free_block(lr);
    }
    else if (size <= 32)
    {
        address = alloc_get_pool_32_free_block(lr);
    }
    else if (size <= 64)
    {
        address = alloc_get_pool_64_free_block(lr);
    }
    else if (size <= 128)
    {
        address = alloc_get_pool_128_free_block(lr);
    }
    else if (size <= 256)
    {
        address = alloc_get_pool_256_free_block(lr);
    }
    else if (size <= 512)
    {
        address = alloc_get_pool_512_free_block(lr);
    }

    /* enable interrupts */
    _enable_irq();

    ASSERT(address != NULL);

    return address;
}

void* malloc(size_t size)
{
    void *address;
    size_t x;

    __asm(
        "mov    %[result], lr"
        : [result]"=r" (x)
        :
        :
    );

    address = _malloc(size, x);
    ASSERT(address != NULL);

    return address;
}

void* calloc(size_t num, size_t size)
{
    void *address;
    size_t x;

    __asm(
        "mov    %[result], lr"
        : [result]"=r" (x)
        :
        :
    );

    address = _malloc(num * size, x);
    ASSERT(address != NULL);
    memset(address, 0, size);

    return address;
}

void free(void *ptr)
{
    ASSERT(ptr != NULL);

    /* disable interrupts */
    _disable_irq();

    *(((uint8_t *)ptr - ALLOC_POOL_HEADER_OFFSET - ALLOC_HEADER_FREE_OFFSET)) = TRUE;
    *(((uint8_t *)ptr - ALLOC_POOL_HEADER_OFFSET - ALLOC_HEADER_LR_OFFSET)) = 0;

    /* enable interrupts */
    _enable_irq();
}
