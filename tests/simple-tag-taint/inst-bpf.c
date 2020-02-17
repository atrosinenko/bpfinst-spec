#include <bpfinst/bpf.h>

#include "inst-common.h"


#define TEST_UN(name) \
  void inst_##name(uint64_t a) {\
    if (tag1()) { \
      set_tag(1); \
    } \
  }

#define TEST_BIN(name) \
  void inst_##name(uint64_t a, uint64_t b) {\
    if (tag1() || tag2()) { \
      set_tag(1); \
    } \
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
TEST_BIN(shl)
TEST_BIN(ashr)
TEST_BIN(lshr)
TEST_BIN(cmp)

TEST_UN(trunc)
TEST_UN(zext)
TEST_UN(sext)

void inst_clz(uint64_t a, uint64_t if0)
{
  if (tag1()) {
    set_tag(1);
  }
}

void inst_ctz(uint64_t a, uint64_t if0)
{
  if (tag1()) {
    set_tag(1);
  }
}

void inst_load(uint64_t addr, int64_t offset)
{
  if (slow_call(-(addr + offset))) {
    set_tag(1);
  }
}

void inst_store(uint64_t addr, int64_t offset, uint64_t value)
{
  if (tag3()) {
    slow_call(addr + offset);
  }
}
