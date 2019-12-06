#include <stdio.h>
#include <stdint.h>

volatile int int32;
volatile long long int64;

int main(int argc, const char *argv[])
{
  scanf("%d %lld", &int32, &int64);

  int32 += 10010;
  int64 += 100100;

  return 0;
}
