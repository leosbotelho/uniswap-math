#include "math.h"
#include <mpfr.h>
#include "mpfr.h"
#include "util.h"

static int Univ3TickBase_b = 0;
static mpfr_t Univ3TickBase_ = {0};

mpfr_ptr Univ3TickBase(void) {
  if (!Univ3TickBase_b) {
    Univ3TickBase_b = 1;
    mpfr_init2(Univ3TickBase_, Prec);
    mpfr_set_str(Univ3TickBase_, "1.0001", 10, MPFR_RNDN);
  }
  return Univ3TickBase_;
}

void clearUniv3TickBase(void) {
  if (Univ3TickBase_b)
    mpfr_clear(Univ3TickBase_);
}

// clang-format off
Univ3TickSpacing univ3FeeTierToTickSpacing(int feeTier) {
  return feeTier == 500   ? 10  :
         feeTier == 3000  ? 60  :
         feeTier == 10000 ? 200 :
                            1   ;
}
// clang-format on

void univ3TickToPrice(Univ3Tick tick, mpfr_t ret) {
  mpfr_pow_si(ret, Univ3TickBase(), tick, MPFR_RNDN);
}

void univ3TickToSqrtPrice(Univ3Tick tick, mpfr_t ret) {
  univ3TickToPrice(tick, ret);
  mpfr_sqrt(ret, ret, MPFR_RNDN);
}

static Univ3Tick univ3Tick_(Univ3TickSpacing tickSpacing, Univ3Tick tick) {
  return (tick / tickSpacing) * tickSpacing;
}

Univ3Tick univ3TickSup(Univ3TickSpacing tickSpacing, Univ3Tick tick) {
  return univ3Tick_(tickSpacing, tick) + (tick > 0) * tickSpacing;
}

Univ3Tick univ3TickInf(Univ3TickSpacing tickSpacing, Univ3Tick tick) {
  return univ3Tick_(tickSpacing, tick) - (tick < 0) * tickSpacing;
}

void univ3x(mpfr_t liquidity,
            mpfr_t sqrtPrice,
            mpfr_t sqrtPriceSup,
            mpfr_t ret_,
            UniReserve* ret) {
  /*
   * (liquidity * (sqrtPriceSup - sqrtPrice)) / (sqrtPrice * sqrtPriceSup)
   */
  mpfr_t d = {0};
  mpfr_init2(d, Prec);
  // d = sqrtPrice * sqrtPriceSup
  mpfr_mul(d, sqrtPrice, sqrtPriceSup, MPFR_RNDN);
  // ret_ = sqrtPriceSup - sqrtPrice
  mpfr_sub(ret_, sqrtPriceSup, sqrtPrice, MPFR_RNDN);
  // ret_ *= liquidity
  mpfr_mul(ret_, ret_, liquidity, MPFR_RNDN);
  // ret_ /= d
  mpfr_div(ret_, ret_, d, MPFR_RNDD);
  //
  char retStr[My_u128MaxDigits + 1] = {0};
  mpfr_snprintf(retStr, My_u128MaxDigits, "%.0Rf", ret_);
  // cleanup
  mpfr_clear(d);
  //
  *ret = u128FromStr(retStr);
}

void univ3y(mpfr_t liquidity,
            mpfr_t sqrtPrice,
            mpfr_t sqrtPriceInf,
            mpfr_t ret_,
            UniReserve* ret) {
  /*
   * liquidity * (sqrtPrice - sqrtPriceInf)
   */
  // ret_ = sqrtPrice - sqrtPriceInf
  mpfr_sub(ret_, sqrtPrice, sqrtPriceInf, MPFR_RNDN);
  // ret_ *= liquidity
  mpfr_mul(ret_, ret_, liquidity, MPFR_RNDN);
  //
  char retStr[My_u128MaxDigits + 1] = {0};
  mpfr_snprintf(retStr, My_u128MaxDigits, "%.0Rf", ret_);
  *ret = u128FromStr(retStr);
}

int univ2MaxAmountOut(UniAmount amountIn,
                      UniReserve x,
                      UniReserve y,
                      UniAmount* ret) {
  /*
   * (amountIn * y) / (amountIn + x)
   */
  *ret = 0;
  if (x == 0 || y == 0 || y == 1)
    return 0;
  /*
   * amountIn is actually 112 bits on Univ2,
   *  so don't worry about overflows here
   *
   * with fee
   */
  amountIn = (amountIn * 997) / 1000;
  My_u256 q = (My_u256)amountIn * (My_u256)y;
  My_u256 d = (My_u256)amountIn + (My_u256)x;
  if (q == d) {
    *ret = 1;
  } else if (q > d) {
    My_u256 ret_ = 0;
    u256Div(q, d, &ret_);
    if (ret_ > My_u256_u112Max)
      // overflow
      return 1;
    *ret = ret_;
  }
  return 0;
}

// univ3MaxAmountOut
