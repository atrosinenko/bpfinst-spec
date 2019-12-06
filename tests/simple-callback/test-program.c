#include <stdio.h>
#include <stdint.h>

volatile int x,  y;

int main(int argc, const char *argv[])
{
  scanf("%d", &x);
  y = x - 11;
  return 0;
}
