#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "mitchell_reeds.h"

/*
 * Algorithm by Don P. Mitchell & James A. Reeds.
 */

enum {
	LEN = 607,
	TAP = 273,
	MASK = 0x7fffffffL,
	A = 48271,
	M = 2147483647,
	Q = 44488,
	R = 3399,
};

Mitchell_Reeds*
mitchell_reeds_init(void)
{
	Mitchell_Reeds *r;

	r = malloc(sizeof(*r));
	if (r == NULL)
		return NULL;
	memset(r, 0, sizeof(*r));

	r->rng_tap = r->rng_vec;

	return r;
}

void
mitchell_reeds_close(Mitchell_Reeds *r)
{
	if (r == NULL)
		return;
	free(r);
}

static void
mitchell_reeds_isrand(Mitchell_Reeds *r, int32_t seed)
{
	int32_t lo, hi, x;
	int i;

	r->rng_tap = r->rng_vec;
	r->rng_feed = r->rng_vec+LEN-TAP;
	seed = seed%M;
	if (seed < 0)
		seed += M;
	if (seed == 0)
		seed = 89482311;
	x = seed;
	/*
	 * Initialize by x[n+1] = 48271 * x[n] mod (2**31 - 1)
	 */
	for (i = -20; i < LEN; i++) {
		hi = x / Q;
		lo = x % Q;
		x = A*lo - R*hi;
		if (x < 0)
			x += M;
		if (i >= 0)
			r->rng_vec[i] = x;
	}
}

void
mitchell_reeds_srand(Mitchell_Reeds *r, int32_t seed)
{
	mitchell_reeds_isrand(r, seed);
};

uint32_t
mitchell_reeds_lrand(Mitchell_Reeds *r)
{
	uint32_t x;

	r->rng_tap--;
	if (r->rng_tap < r->rng_vec) {
		if (r->rng_feed == 0) {
			mitchell_reeds_isrand(r, 1);
			r->rng_tap--;
		}
		r->rng_tap += LEN;
	}
	r->rng_feed--;
	if (r->rng_feed < r->rng_vec)
		r->rng_feed += LEN;
	x = (*r->rng_feed + *r->rng_tap) & MASK;
	*r->rng_feed = x;

	return x;
}
