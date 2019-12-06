#include <bpfinst/bpf.h>

#include "inst-common.h"

void inst_load(uint64_t addr)
{
  size = bit_width_res();
  value = *(uint32_t *)addr;
  slow_call(1);
}

void inst_store(uint64_t addr, uint64_t stored_value)
{
  size = bit_width2();
  value = stored_value;
  slow_call(2);
}
