/**
 *  libcheck-based test suite
 */
#include <stdlib.h>
#include <check.h>
#include "../argv.h"

START_TEST(tst_argv_core_lifecycle) {
	struct argv *vec = argv_init();
	ck_assert(vec != NULL);
	argv_free(vec);
}
END_TEST

START_TEST(tst_argv_core_append) {
	struct argv *vec = argv_init();
	ck_assert(vec != NULL);

	argv_append(vec, "hello");
	argv_append(vec, "world");

	ck_assert_str_eq(vec->argv[0], "hello");
	ck_assert_str_eq(vec->argv[1], "world");

	argv_free(vec);
}
END_TEST

START_TEST(tst_argv_core_find) {
	struct argv *vec = argv_init();
	ck_assert(vec != NULL);

	argv_append(vec, "lorem");
	argv_append(vec, "ipsum");
	argv_append(vec, "dolor");
	argv_append(vec, "sit");
	argv_append(vec, "amet");

	ck_assert_int_eq(argv_find(vec, "dolor"), 2);
	ck_assert_int_eq(argv_find(vec, "sin"), -1);

	argv_free(vec);
}END_TEST

int main() {
	Suite *s = suite_create("argv");
	TCase *tc = tcase_create("argv-core");
	SRunner *sr = srunner_create(s);
	unsigned int nfailed;

	tcase_add_test(tc, tst_argv_core_lifecycle);
	tcase_add_test(tc, tst_argv_core_append);
	tcase_add_test(tc, tst_argv_core_find);
	suite_add_tcase(s, tc);
	
	srunner_run_all(sr, CK_NORMAL);
	nfailed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return nfailed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
