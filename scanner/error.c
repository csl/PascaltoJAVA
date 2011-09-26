#include "global.h"

void error(char *m)
{
	printf(stderr, "line %d: %s\n", lineno, m);
	exit(1);
}

