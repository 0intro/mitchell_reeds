#ifndef _MITCHELL_REEDS_H_
#define _MITCHELL_REEDS_H_ 1
#if defined(__cplusplus)
extern "C" {
#endif

typedef struct Mitchell_Reeds Mitchell_Reeds;

struct Mitchell_Reeds {
	uint32_t rng_vec[607];
	uint32_t *rng_tap;
	uint32_t *rng_feed;
};

Mitchell_Reeds* mitchell_reeds_init();
void mitchell_reeds_srand(Mitchell_Reeds*, int32_t);
uint32_t mitchell_reeds_lrand(Mitchell_Reeds*);
void mitchell_reeds_close(Mitchell_Reeds*);

#if defined(__cplusplus)
}
#endif
#endif
