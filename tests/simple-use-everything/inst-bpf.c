#include <bpfinst/bpf.h>

#include "inst-common.h"

// Test that all args can be used

#define TEST_BIN(name) \
  void inst_##name(uint64_t a, uint64_t b) {\
    arg1 = a | tag1(); \
    arg2 = b | tag2(); \
    slow_call(0); \
    set_tag(arg1 | arg2); \
  }

#define TEST_UN(name) \
  void inst_##name(uint64_t a) {\
    arg1 = a | tag1(); \
    slow_call(0); \
    set_tag(arg1); \
  }

TEST_BIN(add)
TEST_BIN(sub)
TEST_UN(neg)
TEST_BIN(mul)

TEST_BIN(udiv)
TEST_BIN(sdiv)

TEST_BIN(urem)
TEST_BIN(srem_nonneg)
TEST_BIN(srem_1starg)
TEST_BIN(srem_2ndarg)

TEST_BIN(and)
TEST_BIN(nand)
TEST_BIN(or)
TEST_BIN(nor)
TEST_BIN(xor)
TEST_BIN(eqv)
TEST_UN(not)
TEST_BIN(clz)
TEST_BIN(ctz)
TEST_BIN(shl)
TEST_BIN(ashr)
TEST_BIN(lshr)
TEST_BIN(cmp)

TEST_UN(br)
TEST_UN(trunc)
TEST_UN(zext)
TEST_UN(sext)

void inst_load(uint64_t addr, int64_t offset)
{
  uint64_t a = addr + offset;
  arg1 = a | tag1();
  slow_call(0);
  set_tag(arg1);
}

void inst_store(uint64_t addr, int64_t offset, uint64_t value)
{
  uint64_t a = addr + offset;
  uint64_t b = value;
  arg1 = a | tag1();
  arg2 = b | tag3();
  slow_call(0);
  set_tag(arg1 | arg2);
}
