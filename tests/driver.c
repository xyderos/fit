#include <assert.h>
#include <check.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "driver.h"

blk_t *first_hole = NULL;

int
main(void)
{
	int no_failed = 0;
	Suite *s = NULL;
	SRunner *runner = NULL;

	s = best_fit_suite();
	runner = srunner_create(s);
	srunner_add_suite(runner, first_fit_suite());
	srunner_add_suite(runner, next_fit_suite());
	srunner_add_suite(runner, worst_fit_suite());

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
