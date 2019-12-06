#include <stdint.h>

int my_memcmp(const void *_s1, const void *_s2, size_t n)
{
  uint8_t *s1 = (uint8_t *)_s1;
  uint8_t *s2 = (uint8_t *)_s2;
  for (int i = 0; i < n; ++i) {
    if (s1[i] != s2[i]) {
      return (int)s1[i] - (int)s2[i];
    }
  }
  return 0;
}

size_t my_strlen(const char *s)
{
  size_t res = 0;
  while (*s) {
    res += 1;
    s += 1;
  }
  return res;
}
