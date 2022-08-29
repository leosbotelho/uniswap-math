#include "type.h"

const My_u128 My_u112Max = ((My_u128)1 << 112) - 1;
const My_u128 My_u128Max = 2 * (((My_u128)1 << 127) - 1) + 1;

const My_u256 My_u256_u112Max = My_u112Max;
const My_u256 My_u256_u128Max = My_u128Max;
