#pragma once
#include <check.h>
#include <stdlib.h>

#include "../../src/next_fit/next_fit.h"

extern blk_t *first_hole;

Suite *next_fit_suite(void);

START_TEST(test_next_fit_no_holes)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = NULL;
	allocated_block = next_fit(size);

	ck_assert_ptr_eq(allocated_block, NULL);
}
END_TEST

START_TEST(test_next_fit_next_available_hole)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 50;
	first_hole->start_address = 100;
	first_hole->next = malloc(sizeof(blk_t));
	first_hole->previous = NULL;
	first_hole->next->size = 150;
	first_hole->next->start_address = 250;
	first_hole->next->next = NULL;
	first_hole->next->previous = first_hole;

	allocated_block = next_fit(size);

	ck_assert_ptr_nonnull(allocated_block);
	ck_assert_int_eq(allocated_block->size, size);
	ck_assert_int_eq(allocated_block->start_address, 250);

	block_deallocate(allocated_block);
	free(first_hole->next);
	free(first_hole);
	first_hole = NULL;
}
END_TEST

START_TEST(test_next_fit_wrap_around)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 50;
	first_hole->start_address = 100;
	first_hole->next = malloc(sizeof(blk_t));
	first_hole->next->size = 80;
	first_hole->next->start_address = 200;
	first_hole->next->next = malloc(sizeof(blk_t));
	first_hole->next->next->size = 150;
	first_hole->next->next->start_address = 300;
	first_hole->next->next->next = NULL;

	allocated_block = next_fit(10);
	block_deallocate(allocated_block);

	next_fit(200);

	allocated_block = next_fit(size);

	ck_assert_ptr_nonnull(allocated_block);
	ck_assert_int_eq(allocated_block->size, size);
	ck_assert_int_eq(allocated_block->start_address, 300);

	block_deallocate(allocated_block);

	free(first_hole->next->next);
	free(first_hole->next);
	free(first_hole);
}
END_TEST

START_TEST(test_next_fit_too_large)
{
	ul_t size = 100;
	blk_t *allocated_block = NULL;

	first_hole = malloc(sizeof(blk_t));
	first_hole->size = 90;
	first_hole->start_address = 0;
	first_hole->next = NULL;

	allocated_block = next_fit(size);

	ck_assert_ptr_eq(allocated_block, NULL);

	free(first_hole);
	first_hole = NULL;
}
END_TEST
