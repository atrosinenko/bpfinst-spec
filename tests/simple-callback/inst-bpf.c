#include <bpfinst/bpf.h>

void inst_sub(uint64_t a, uint64_t b) {\
  uint32_t t = slow_call(a);
  slow_call(b + t);
}
