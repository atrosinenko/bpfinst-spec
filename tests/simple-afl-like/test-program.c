#include <stdio.h>

volatile int x;

int main(int argc, const char *argv[])
{
  int n;
  int res = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    x = i;
    res += x * x;
  }
  printf("res = %d\n", res);
  return 0;
}
