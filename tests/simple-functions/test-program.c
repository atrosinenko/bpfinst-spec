#include <stdio.h>
#include <stdint.h>

volatile int x, y, z, r;

int __attribute__((noinline)) f(int x, int y)
{
  return x + y;
}

int main(int argc, const char *argv[])
{
  scanf("%d %d %d", &x, &y, &z);

  r = f(x & z, y & z);

  fprintf(stderr, "%d\n", r);

  z = r - z;

  return 0;
}
