#include <bpfinst/bpf.h>

#include "inst-common.h"


#define TEST_UN(name) \
  void inst_##name(uint64_t a) {\
    set_tag(tag1()); \
  }

#define TEST_BIN(name) \
  void inst_##name(uint64_t a, uint64_t b) {\
    set_tag(tag1() | tag2()); \
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
TEST_BIN(clz)
TEST_BIN(ctz)
TEST_UN(not)
TEST_BIN(shl)
TEST_BIN(ashr)
TEST_BIN(lshr)
TEST_BIN(cmp)

TEST_UN(trunc)
TEST_UN(zext)
TEST_UN(sext)

void inst_load(uint64_t addr, int64_t offset)
{
  arg1 = addr + offset;
  set_tag(slow_call(GET_TAG) | tag1());
}

void inst_store(uint64_t addr, int64_t offset, uint64_t value)
{
  arg1 = addr + offset;
  arg2 = tag1() | tag3();
  slow_call(SET_TAG);
}
