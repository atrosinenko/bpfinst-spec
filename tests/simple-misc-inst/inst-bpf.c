#include <bpfinst/bpf.h>

#include "inst-common.h"

#define TEST_BIN(funct, name) \
  void inst_##name(uint64_t a, uint64_t b) {\
    arg1 = a; \
    arg2 = b; \
    slow_call(funct); \
  }

TEST_BIN(1, add)
TEST_BIN(2, sub)
TEST_BIN(3, mul)

TEST_BIN(4, udiv)
TEST_BIN(4, sdiv)

TEST_BIN(5, urem)
TEST_BIN(5, srem_nonneg)
TEST_BIN(5, srem_1starg)
TEST_BIN(5, srem_2ndarg)

TEST_BIN(6, and)
TEST_BIN(7, or)
TEST_BIN(8, xor)
TEST_BIN(9, shl)
TEST_BIN(10, ashr)
TEST_BIN(11, lshr)
