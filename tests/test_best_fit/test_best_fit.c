#include "test_best_fit.h"

Suite *
best_fit_suite(void)
{
	Suite *s = suite_create("best_fit");
	TCase *tc_core = tcase_create("core");

	tcase_add_test(tc_core, test_best_fit_no_holes);
	tcase_add_test(tc_core, test_best_fit_exact_match);
	tcase_add_test(tc_core, test_best_fit_selection);
	tcase_add_test(tc_core, test_best_fit_too_large);

	suite_add_tcase(s, tc_core);
	return s;
}
