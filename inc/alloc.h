#ifndef _ALLOC_H_
#define _ALLOC_H_

#include "stdlib.h"
#include "embedded_types.h"


#define ALLOC_POOL_4_BLOCKS 128
#define ALLOC_POOL_8_BLOCKS 128
#define ALLOC_POOL_16_BLOCKS 128
#define ALLOC_POOL_32_BLOCKS 128
#define ALLOC_POOL_64_BLOCKS 128
#define ALLOC_POOL_128_BLOCKS 1
#define ALLOC_POOL_256_BLOCKS 1
#define ALLOC_POOL_512_BLOCKS 1


typedef struct pool_header_tag
{
    size_t lr;
    bool free;
} pool_header_t;

typedef struct pool_4_block_tag
{
    pool_header_t header;
    uint8_t data[4];
} pool_4_block_t;

typedef struct pool_8_block_tag
{
    pool_header_t header;
    uint8_t data[8];
} pool_8_block_t;

typedef struct pool_16_block_tag
{
    pool_header_t header;
    uint8_t data[16];
} pool_16_block_t;

typedef struct pool_32_block_tag
{
    pool_header_t header;
    uint8_t data[32];
} pool_32_block_t;

typedef struct pool_64_block_tag
{
    pool_header_t header;
    uint8_t data[64];
} pool_64_block_t;

typedef struct pool_128_block_tag
{
    pool_header_t header;
    uint8_t data[128];
} pool_128_block_t;

typedef struct pool_256_block_tag
{
    pool_header_t header;
    uint8_t data[256];
} pool_256_block_t;

typedef struct pool_512_block_tag
{
    pool_header_t header;
    uint8_t data[512];
} pool_512_block_t;

typedef struct pool_tag
{
    pool_4_block_t pool_4[ALLOC_POOL_4_BLOCKS];
    pool_8_block_t pool_8[ALLOC_POOL_8_BLOCKS];
    pool_16_block_t pool_16[ALLOC_POOL_16_BLOCKS];
    pool_32_block_t pool_32[ALLOC_POOL_32_BLOCKS];
    pool_64_block_t pool_64[ALLOC_POOL_64_BLOCKS];
    pool_128_block_t pool_128[ALLOC_POOL_128_BLOCKS];
    pool_256_block_t pool_256[ALLOC_POOL_256_BLOCKS];
    pool_512_block_t pool_512[ALLOC_POOL_512_BLOCKS];
} pool_t;


#define ALLOC_POOL_HEADER_OFFSET \
    FIELD_OFFSET(pool_4_block_t, header)
#define ALLOC_HEADER_LR_OFFSET \
    FIELD_OFFSET(pool_header_t, lr)
#define ALLOC_HEADER_FREE_OFFSET \
    FIELD_OFFSET(pool_header_t, free)


void alloc_init(void);
void* alloc_get_pool_4_free_block(size_t lr);
void* alloc_get_pool_8_free_block(size_t lr);
void* alloc_get_pool_16_free_block(size_t lr);
void* alloc_get_pool_32_free_block(size_t lr);
void* alloc_get_pool_64_free_block(size_t lr);
void* alloc_get_pool_128_free_block(size_t lr);
void* alloc_get_pool_256_free_block(size_t lr);
void* alloc_get_pool_512_free_block(size_t lr);
void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void free(void *ptr);

#endif /* _ALLOC_H_ */
