#include "test_first_fit.h"

Suite *
first_fit_suite(void)
{
	Suite *s = suite_create("first_fit");
	TCase *tc_core = tcase_create("core");

	tcase_add_test(tc_core, test_first_fit_no_holes);
	tcase_add_test(tc_core, test_first_fit_first_suitable_hole);
	tcase_add_test(tc_core, test_first_fit_exact_size);
	tcase_add_test(tc_core, test_first_fit_too_large);

	suite_add_tcase(s, tc_core);
	return s;
}
