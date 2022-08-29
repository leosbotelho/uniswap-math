#ifndef My_Util_Hdr
#define My_Util_Hdr

#include "type.h"

extern unsigned readDigit(char d);

extern My_u128 u128FromStr(const char* s);

extern void u128ToStr(My_u128 n, char* ret);

extern void pp_u128_(My_u128 n);
extern void pp_u128(My_u128 n);

extern void u256Div(My_u256 q, My_u256 d, My_u256* ret);

#endif
