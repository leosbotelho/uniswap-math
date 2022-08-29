#ifndef My_Math_Hdr
#define My_Math_Hdr

#include <mpfr.h>
#include "type.h"

extern Univ3TickSpacing univ3FeeTierToTickSpacing(int feeTier);

extern mpfr_ptr Univ3TickBase(void);

extern void clearUniv3TickBase(void);

extern void univ3TickToPrice(Univ3Tick tick, mpfr_t ret);
extern void univ3TickToSqrtPrice(Univ3Tick tick, mpfr_t ret);

extern Univ3Tick univ3TickInf(Univ3TickSpacing tickSpacing, Univ3Tick tick);
extern Univ3Tick univ3TickSup(Univ3TickSpacing tickSpacing, Univ3Tick tick);

extern void univ3x(mpfr_t liquidity,
                   mpfr_t sqrtPrice,
                   mpfr_t sqrtPriceSup,
                   mpfr_t ret_,
                   UniReserve* ret);

extern void univ3y(mpfr_t liquidity,
                   mpfr_t sqrtPrice,
                   mpfr_t sqrtPriceInf,
                   mpfr_t ret_,
                   UniReserve* ret);

extern int univ2MaxAmountOut(UniAmount amountIn,
                             UniReserve x,
                             UniReserve y,
                             UniAmount* ret);

// univ3MaxAmountOut

#endif
