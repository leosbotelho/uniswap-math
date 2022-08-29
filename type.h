#ifndef My_Type_Hdr
#define My_Type_Hdr

#include <assert.h>

typedef unsigned __int128 My_u128;
typedef unsigned _ExtInt(256) My_u256;

enum { My_u128MaxDigits = 39, My_u112MaxDigits = 34 };

extern const My_u128 My_u112Max;
extern const My_u128 My_u128Max;

extern const My_u256 My_u256_u112Max;
extern const My_u256 My_u256_u128Max;

typedef My_u128 UniLiquidity;
typedef My_u128 UniReserve;
typedef My_u128 UniAmount;

enum {
  UniLiquiditySz = sizeof(UniLiquidity),
  UniReserveSz = sizeof(UniReserve),
  UniAmountSz = sizeof(UniAmount)
};

typedef long Univ3Tick;
typedef long Univ3TickSpacing;

enum {
  Univ3TickSz = sizeof(Univ3Tick),
  Univ3TickSpacingSz = sizeof(Univ3TickSpacing)
};

#endif
