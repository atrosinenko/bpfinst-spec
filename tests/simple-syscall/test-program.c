#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, const char *argv[])
{
  char digits[2];
  assert(read(0, digits, 2) == 2);
  int x = digits[0] - '0';
  int y = digits[1] - '0';
  fprintf(stderr, "PRINT %d\n", x + y);
  fprintf(stderr, "NOPRINT %d\n", x + y);
  return 0;
}
