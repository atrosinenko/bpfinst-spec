#include <stdio.h>
#include <stdint.h>

volatile long long x,  y, z;

int main(int argc, const char *argv[])
{
  scanf("%lld %lld", &x, &y);

  z = x - y;

  return 0;
}
