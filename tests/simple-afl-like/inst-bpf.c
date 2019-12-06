#include <bpfinst/bpf.h>

#include "inst-common.h"

static uint64_t prev;

void inst_br(uint64_t cond)
{
  afl_map[((prev >> 1) ^ pseudo_pc()) & 0xffff] += 1;
  prev = pseudo_pc();
}
