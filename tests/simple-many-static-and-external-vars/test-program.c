#include <stdio.h>
#include <stdint.h>

volatile int x,  y, z;

int main(int argc, const char *argv[])
{
  scanf("%d %d", &x, &y);

  x -= 123;
  y /= 123;

  scanf("%d %d", &x, &y);
  x -= 321;
  y /= 321;

  z = x * 321;

  return 0;
}
