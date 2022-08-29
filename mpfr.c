#include "mpfr.h"
#include <assert.h>
#include <mpfr.h>
#include "math.h"

mpfr_t My_one = {0}, My_half = {0};

void tightenMpfr(void) {
  mpfr_set_default_prec(Prec);
  mpfr_set_emin(Emin);
  mpfr_set_emax(Emax);
}

static int mpfrIsInit = 0;

void initMpfr(void) {
  assert(!mpfrIsInit);
  if (!mpfrIsInit) {
    mpfrIsInit = 1;
    tightenMpfr();
    mpfr_inits2(Prec, My_one, My_half, (mpfr_ptr)0);
    mpfr_set_si(My_one, 1, MPFR_RNDN);
    mpfr_set_str(My_half, "0.5", 10, MPFR_RNDN);
  }
}

void cleanupMpfr(void) {
  assert(mpfrIsInit);
  if (mpfrIsInit) {
    mpfr_clears(My_one, My_half, (mpfr_ptr)0);
    clearUniv3TickBase();
    mpfr_mp_memory_cleanup();
  }
}
