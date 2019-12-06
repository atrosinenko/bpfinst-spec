#include <bpfinst/bpf.h>

void inst_sub(uint64_t a, uint64_t b)
{
  // expands into quite large listing
  uint64_t pa = __builtin_popcountll(a);
  uint64_t pb = __builtin_popcountll(b);

  slow_call(pa);
  slow_call(pb);
  slow_call(pa * pb);

  if (pa < pb)
    slow_call(pa);
  else if (pa == pb)
    slow_call(-1);
  else
    slow_call(pb);
}
