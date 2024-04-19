#include <stdlib.h>

#include "worst_fit.h"

extern blk_t *first_hole;

blk_t *
worst_fit(ul_t size)
{
	blk_t *current_hole = first_hole, *worst_hole = NULL;

	ul_t maxSize = 0;

	while (current_hole) {

		if (current_hole->size >= maxSize &&
		    current_hole->size >= size) {
			maxSize = current_hole->size;
			worst_hole = current_hole;
		}
		current_hole = current_hole->next;
	}

	current_hole = worst_hole;

	if (!current_hole) {
		return NULL;
	}

	return block_allocate(current_hole, size);
}
