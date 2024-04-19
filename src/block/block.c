#include <stdlib.h>

#include "block.h"

extern blk_t *first_hole;
static blk_t *first_object;

blk_t *
first_allocation(ul_t size)
{
	void *main_memory_block = malloc(size);

	if (!main_memory_block) {
		return NULL;
	}

	return main_memory_block;
}

static blk_t *
blk_allocate(blk_t *current_hole, ul_t size)
{
	blk_t *new_object = (blk_t *)malloc(sizeof(blk_t));

	new_object->size = size;
	new_object->start_address = current_hole->start_address;
	new_object->next = NULL;
	new_object->previous = NULL;

	return new_object;
}

blk_t *
block_allocate(blk_t *current_hole, ul_t size)
{
	blk_t *new_object = blk_allocate(current_hole, size),
	      *previous_hole = current_hole->previous,
	      *next_hole = current_hole->next, *previous_object = NULL,
	      *next_object = NULL, *current_object = NULL;

	if (current_hole->size == size) {
		if (previous_hole) {
			previous_hole->next = next_hole;
		} else {
			first_hole = next_hole;
		}

		if (next_hole) {
			next_hole->previous = previous_hole;
		}

		free(current_hole);
	} else {

		current_hole->size -= size;
		current_hole->start_address += size;
	}

	if (!first_object) {

		first_object = new_object;
		return new_object;
	}

	current_object = first_object;

	while (current_object) {
		if (current_object->start_address < new_object->start_address) {
			previous_object = current_object;
			next_object = current_object->next;
		} else {
			next_object = current_object;
			break;
		}

		current_object = current_object->next;
	}

	if (previous_object) {
		previous_object->next = new_object;
		new_object->previous = previous_object;
	} else {
		first_object = new_object;
	}

	if (next_object) {
		new_object->next = next_object;
		next_object->previous = new_object;
	}

	return new_object;
}

void
block_deallocate(blk_t *object)
{
	blk_t *previous_object = object->previous, *next_object = object->next,
	      *current_hole = first_hole, *previous_hole = NULL,
	      *next_hole = NULL;

	if (!object) {
		return;
	}

	if (previous_object) {
		previous_object->next = next_object;
	}

	if (next_object) {

		next_object->previous = previous_object;

		if (first_object == object && !previous_object) {
			first_object = next_object;
		}
	}

	if (!next_object && !previous_object) {
		first_object = NULL;
	}

	while (current_hole) {

		if (current_hole->start_address < object->start_address) {

			previous_hole = current_hole;
			next_hole = current_hole->next;
		} else {
			next_hole = current_hole;
			break;
		}

		current_hole = current_hole->next;
	}

	if (!next_hole && !previous_hole) {
		first_hole = object;
		first_hole->next = NULL;
		first_hole->previous = NULL;

		return;
	}

	if (previous_hole) {

		previous_hole->next = object;
		object->previous = previous_hole;

		if (previous_hole->start_address + previous_hole->size ==
		    object->start_address) {

			object->size += previous_hole->size;
			object->start_address = previous_hole->start_address;
			object->previous = previous_hole->previous;
			if (previous_hole->previous) {
				previous_hole->previous->next = object;
			}

			if (previous_hole == first_hole) {
				first_hole = object;
			}

			free(previous_hole);
		}
	}

	if (next_hole) {

		object->next = next_hole;
		next_hole->previous = object;
		if (object->start_address + object->size ==
		    next_hole->start_address) {

			object->size += next_hole->size;
			object->next = next_hole->next;
			if (next_hole->next) {
				next_hole->next->previous = object;
			}

			if (next_hole == first_hole) {
				first_hole = object;
			}
			free(next_hole);
		}
	}

	while (first_hole->previous) {
		first_hole = first_hole->previous;
	}
}
