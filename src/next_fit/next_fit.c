#include <stdlib.h>

#include "next_fit.h"

extern blk_t *first_hole;

static ul_t last_allocated_address = 0;

blk_t *
next_fit(ul_t size)
{
	blk_t *current_hole = first_hole, *first_hole_before_last = NULL;

	while (current_hole) {
		if (!first_hole_before_last &&
		    current_hole->start_address < last_allocated_address &&
		    current_hole->size >= size) {

			first_hole_before_last = current_hole;
		}

		if (current_hole->start_address >= last_allocated_address &&
		    current_hole->size >= size) {
			break;
		}

		current_hole = current_hole->next;
	}

	if (!current_hole && !first_hole_before_last) {
		return NULL;
	}

	if (!current_hole) {
		current_hole = first_hole_before_last;
	}

	last_allocated_address = current_hole->start_address;

	return block_allocate(current_hole, size);
}
