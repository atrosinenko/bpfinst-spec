#define EBPF
#include "../lib/trivial-test.h"

BEGIN_EBPF_HANDLER
  BEGIN_INPUTS
  EXPECT_INPUT(127, 257)
  EXPECT_INPUT(20, 19)
  EXPECT_INPUT(129, 257)
  EXPECT_INPUT(1000000000001LLu, 2)
  END_INPUTS

  // expands into quite large listing
  uint64_t pa = __builtin_popcountll(arg1);
  uint64_t pb = __builtin_popcountll(arg2);

  slow_call(pa);
  slow_call(pb);
  slow_call(pa * pb);

  if (pa < pb)
    slow_call(pa);
  else if (pa == pb)
    slow_call(-1);
  else
    slow_call(pb);

END_EBPF_HANDLER
