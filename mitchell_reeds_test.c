#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mitchell_reeds.h"

int
main()
{
	Mitchell_Reeds *r;
	uint8_t buf[2048];
	unsigned int i, n;

	r = mitchell_reeds_init();
	if (r == NULL)
		return 1;

	mitchell_reeds_srand(r, 42);

	for (i = 0; i < sizeof(buf); i+=4) {
		n = mitchell_reeds_lrand(r);
		buf[i+0] = n >> 24;
		buf[i+1] = n >> 16;
		buf[i+2] = n >> 8;
		buf[i+3] = n;
	}

	mitchell_reeds_close(r);

	for (i = 0; i < sizeof(buf); i++)
		printf("%u ", buf[i]);
	printf("\n");

	return 0;
}
