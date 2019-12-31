#include <stdio.h>
#include <stdint.h>

volatile uint64_t array[1 << 16][3][4];

volatile uint64_t t_value, t_tag;

uint64_t get_int_tagged_with_self(void)
{
  int result;
  scanf("%d", &result);

  t_value = result;
  t_tag = result;

  return t_value;
}

int main(int argc, const char *argv[])
{
  // Make instrumenter know locations of `value` and `tag`
  t_value = 100501;
  t_tag   = 100502;
  // Now, reading from `value` returns value tagged with `tag`

  uint64_t idx1, idx2, idx3;

  idx1 = get_int_tagged_with_self();
  idx2 = get_int_tagged_with_self();
  idx3 = get_int_tagged_with_self();

  fprintf(stderr, "Indices: %d %d %d\n", idx1, idx2, idx3);
  fprintf(stderr, "Offset is %d.\n", (int)(&array[idx1][idx2][idx3]) - (int)array);
  array[idx1][idx2][idx3] = 1001;

  return 0;
}
