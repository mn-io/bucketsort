//based on http://www.jera.com/techinfo/jtns/jtn002.html
#include <stdio.h>
#include <assert.h>

 #define mu_run_test(test) do {\
	test();\
	tests_run++;\
	printf("%i. passed in %s:%d\n", tests_run, __FILE__, __LINE__);\
    } while (0)

 int tests_run = 0;
