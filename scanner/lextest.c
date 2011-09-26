
#include<stdio.h>
#include "global.h"

int main()
{
	int p = 0;
	init();
	while (1)	
	{
		p = lexan();
		printf("<%d, %d>\n", p, tokenval);
		if (p == 260)
		{
			printf("\n");
			break;
		}
	}
}
