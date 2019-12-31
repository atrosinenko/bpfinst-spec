#include <stdio.h>
#include <stdint.h>

struct test {
  uint32_t x;
  uint64_t y; // aligned at 8
};

struct test array[10];

volatile uint64_t t_value;

volatile uintptr_t a;

volatile struct test *tagged_ptr;
volatile uint64_t *y_ptr;

int main(int argc, const char *argv[])
{
  // Make instrumenter know location of `value`
  t_value = 100501;
  // Now, reading from `value` returns value with itself

  uint64_t idx;
  scanf("%d", &idx);

  t_value = (uint64_t)array;
  tagged_ptr = (struct test *)t_value;

  y_ptr = &tagged_ptr[idx].y;
  a = (uintptr_t)y_ptr - (uintptr_t)tagged_ptr;

  return 0;
}
