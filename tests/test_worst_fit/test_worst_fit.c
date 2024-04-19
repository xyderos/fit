#include "test_worst_fit.h"

Suite *
worst_fit_suite(void)
{
	Suite *s = suite_create("worst_fit");
	TCase *tc_core = tcase_create("core");

	tcase_add_test(tc_core, test_worst_fit_no_holes);
	tcase_add_test(tc_core, test_worst_fit_largest_hole);
	tcase_add_test(tc_core, test_worst_fit_multiple_same_size);
	tcase_add_test(tc_core, test_worst_fit_too_large);

	suite_add_tcase(s, tc_core);
	return s;
}
