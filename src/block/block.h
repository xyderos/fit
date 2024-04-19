#pragma once

typedef unsigned long ul_t;

typedef struct blk {
	ul_t size, start_address;
	struct blk *next, *previous;
} blk_t;

blk_t *first_allocation(ul_t size);
blk_t *block_allocate(blk_t *current_hole, ul_t size);
void block_deallocate(blk_t *object);
