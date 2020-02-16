#define EBPF
#include "../lib/trivial-test.h"

BEGIN_EBPF_HANDLER
  BEGIN_INPUTS
  EXPECT_INPUT(100, 11)
  END_INPUTS

  uint32_t t = slow_call(arg1);
  slow_call(arg2 + t);

END_EBPF_HANDLER
