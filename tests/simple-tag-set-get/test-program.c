#include <stdio.h>
#include <stdint.h>

volatile int x, y, z;

int main(int argc, const char *argv[])
{
  scanf("%d %lu", &x, &y);

  z = x + y + 100500;

  return 0;
}
