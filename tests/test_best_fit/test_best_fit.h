#pragma once

#include <check.h>
#include <stdlib.h>

#include "../../src/best_fit/best_fit.h"

extern blk_t *first_hole;

Suite *best_fit_suite(void);

START_TEST(test_best_fit_no_holes)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = NULL;

	allocated_block = best_fit(size);

	ck_assert_ptr_eq(allocated_block, NULL);
	first_hole = NULL;
}
END_TEST

START_TEST(test_best_fit_exact_match)
{
	ul_t size = 150;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 150;
	first_hole->start_address = 100;
	first_hole->next = NULL;
	first_hole->previous = NULL;

	allocated_block = best_fit(size);

	ck_assert_ptr_nonnull(allocated_block);
	ck_assert_int_eq(allocated_block->size, size);
	ck_assert_int_eq(allocated_block->start_address, 100);

	block_deallocate(allocated_block);
	free(first_hole);
	first_hole = NULL;
}
END_TEST

START_TEST(test_best_fit_selection)
{
	ul_t size = 50;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 300;
	first_hole->start_address = 0;
	first_hole->next = malloc(sizeof(blk_t));
	first_hole->previous = NULL;
	first_hole->next->size = 200;
	first_hole->next->start_address = 300;
	first_hole->next->next = malloc(sizeof(blk_t));
	first_hole->next->previous = first_hole;
	first_hole->next->next->size = 100;
	first_hole->next->next->start_address = 500;
	first_hole->next->next->next = NULL;
	first_hole->next->next->previous = first_hole->next;

	allocated_block = best_fit(size);

	ck_assert_ptr_nonnull(allocated_block);
	ck_assert_int_eq(allocated_block->size, size);
	ck_assert_int_eq(allocated_block->start_address, 500);

	block_deallocate(allocated_block);

	free(first_hole->next->next);
	free(first_hole->next);
	free(first_hole);
	first_hole = NULL;
}
END_TEST

START_TEST(test_best_fit_too_large)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 50;
	first_hole->start_address = 0;
	first_hole->next = NULL;

	allocated_block = best_fit(size);

	ck_assert_ptr_eq(allocated_block, NULL);

	free(first_hole);
	first_hole = NULL;
}
END_TEST
