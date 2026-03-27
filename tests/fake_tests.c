#include "utest.h"

static void fake_test(void)
{
	ASSERT(1 == 1);
}

int main(void)
{
	RUN_TEST(fake_test);

	TEST_SUMMARY();
	TEST_EXIT();
}
