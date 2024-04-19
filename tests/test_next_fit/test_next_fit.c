
#include "test_next_fit.h"

Suite *
next_fit_suite(void)
{
	Suite *s = suite_create("next_fit");
	TCase *tc_core = tcase_create("core");

	tcase_add_test(tc_core, test_next_fit_no_holes);
	tcase_add_test(tc_core, test_next_fit_next_available_hole);
	tcase_add_test(tc_core, test_next_fit_wrap_around);
	tcase_add_test(tc_core, test_next_fit_too_large);

	suite_add_tcase(s, tc_core);
	return s;
}
