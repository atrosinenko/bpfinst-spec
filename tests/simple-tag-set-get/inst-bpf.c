#include <bpfinst/bpf.h>

void inst_add(uint64_t a, uint64_t b)
{
  if (a + b == 1001) {
    set_tag(123);
    slow_call(-1);
  }
  if (a == 100500) {
    slow_call(-2);
    slow_call(tag2());
  }
  if (b == 100500) {
    slow_call(-2);
    slow_call(tag1());
  }
}
