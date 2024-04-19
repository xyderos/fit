#include <limits.h>
#include <stdlib.h>

#include "best_fit.h"

extern blk_t *first_hole;

blk_t *
best_fit(ul_t size)
{
	blk_t *current_hole = first_hole, *best_hole = NULL;

	ul_t minDiff = INT_MAX, diff = 0;

	while (current_hole) {
		diff = (current_hole->size - size);
		if (diff < minDiff && diff >= 0) {
			minDiff = diff;
			best_hole = current_hole;
		}
		current_hole = current_hole->next;
	}

	current_hole = best_hole;

	if (!current_hole) {
		return NULL;
	}

	return block_allocate(current_hole, size);
}
