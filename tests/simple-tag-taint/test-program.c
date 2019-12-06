#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <syscall.h>

int main(int argc, const char *argv[])
{
  int32_t tx, ty, u, v;
  syscall(10001, &tx);
  syscall(10001, &ty);
  scanf("%d", &u);
  scanf("%d", &v);

  int ta = tx + ty;
  int tb = tx * 7 + 1;
  int tc = ta + u;
  int d = u + 2;
  int e = u + v;

  syscall(20002, &ta);
  syscall(20002, &tb);
  syscall(20002, &tc);
  syscall(20002, &d);
  syscall(20002, &e);
  return 0;
}
