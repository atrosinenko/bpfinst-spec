#include <stdio.h>
#include <syscall.h>
#include <stdio.h>

#include <bpfinst/native.h>

static int nocatch;

uint64_t event_before_syscall(uint32_t num, uint32_t *drop_syscall,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
  if (num == SYS_read && arg1 == 0) {
    fprintf(stderr, "Intercepted read(stdin, ...)\n");
  }
  if (num == SYS_write && arg1 == 2 && !nocatch) {
    *drop_syscall = ((char *)arg2)[0] == 'N';
    nocatch = 1;
    fprintf(stderr, "Intercepted write(stderr, ...), %s...\n", *drop_syscall ? "dropping" : "passing");
    nocatch = 0;
    return arg3;
  }
  return 0;
}
