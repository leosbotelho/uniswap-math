#include "util.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

unsigned readDigit(char d) {
  if (d >= (char)0x30 && d <= (char)0x39)
    return d - 0x30;
  return -1;
}

My_u128 u128FromStr(const char* s) {
  My_u128 ret = 0;
  for (; *s != 0; s++) {
    ret *= 10;
    ret += readDigit(*s);
  }
  return ret;
}

void u128ToStr(My_u128 n, char* ret) {
  static_assert(sizeof(unsigned long) == 8, "");
  static const unsigned long d = 10000000000000000000UL;
  char buf[3][21] = {0};
  int i = 0;
  while (i++ < 3) {
    if (n > ULONG_MAX) {
      unsigned long lo = n % d;
      snprintf(buf[i - 1], 20, "%.19lu", lo);
      n /= d;
    } else {
      snprintf(buf[i - 1], 21, "%lu", (unsigned long)n);
      break;
    }
  }
  strcpy(ret, buf[i - 1]);
  if (i > 1) {
    strcat(ret, buf[i - 2]);
    if (i > 2)
      strcat(ret, buf[i - 3]);
  }
}

void pp_u128_(My_u128 n) {
  char s[My_u128MaxDigits + 1] = {0};
  u128ToStr(n, s);
  fputs(s, stdout);
}

void pp_u128(My_u128 n) {
  pp_u128_(n);
  fputc('\n', stdout);
}

void u256Div(My_u256 q, My_u256 d, My_u256* ret) {
  *ret = 0;
  while (q >= d) {
    My_u256 d_ = d;
    My_u256 i = 0;
    for (; q >= (d_ << 1); i++)
      d_ <<= 1;
    *ret |= (My_u256)1 << i;
    q -= d_;
  }
}
