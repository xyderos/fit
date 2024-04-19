#include <stdlib.h>

#include "first_fit.h"

extern blk_t *first_hole;

blk_t *
first_fit(ul_t size)
{
	blk_t *current_hole = first_hole;

	while (current_hole) {

		if (current_hole->size >= size) {
			break;
		}
		current_hole = current_hole->next;
	}

	if (!current_hole) {
		return NULL;
	}

	return block_allocate(current_hole, size);
}
