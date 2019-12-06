#include <stdio.h>
#include <stdint.h>

volatile int x,  y;
volatile unsigned ux, uy;

int main(int argc, const char *argv[])
{
  scanf("%d %lu", &x, &ux);

  y = x + 11;
  y = x - 12;
  y = x * 13;
  y = x / 14;
  y = x % 15;
  y = x & 16;
  y = x | 17;
  y = x ^ 18;
  y = x << 19;
  y = x >> 20;
  uy = ux >> 21;
  return 0;
}
