#ifndef My_Mpfr_Hdr
#define My_Mpfr_Hdr

extern mpfr_t My_one, My_half;

/*
 * take:
 *   inf = (1 / 2) * (2 ^ emin)
 *   sup = (1 - 1 / (2 ^ prec)) * (2 ^ emax)
 *
 * for our purposes,
 *   we want [1 / (2^128 - 1), 2^128 - 1] in range
 *
 *   overall, we need something like prec = 2 * 128 = 256
 *
 * do the math
 */

enum { HalfPrec = 128 };
enum { Prec = 2 * HalfPrec };

enum { Emin = -129 };
enum { Emax = 132 };

extern void tightenMpfr(void);

extern void initMpfr(void);

extern void cleanupMpfr(void);

#endif
