#ifndef FUZZER_UTILS_H
#define FUZZER_UTILS_H

#include <bpfinst/native.h>

#include <syscall.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void setup_watchdog_timer(int max_millis)
{
  // Set limit on active CPU usage
  struct rlimit lim;
  lim.rlim_cur = max_millis / 1000;
  lim.rlim_max = max_millis / 1000;
  setrlimit(RLIMIT_CPU, &lim);

  // Set less robust limit on wall-clock execution time
  struct itimerspec tval;
  struct sigevent sigev;
  timer_t timer_id;

  memset(&tval, 0, sizeof(tval));
  tval.it_value.tv_sec = max_millis / 1000;
  tval.it_value.tv_nsec = (max_millis % 1000) * 1000000;

  memset(&sigev, 0, sizeof(sigev));
  sigev.sigev_notify = SIGEV_SIGNAL;
  sigev.sigev_signo = SIGKILL;

  if (timer_create(CLOCK_MONOTONIC, &sigev, &timer_id) != 0) {
    abort();
  }
  if (timer_settime(timer_id, 0, &tval, NULL) != 0) {
    abort();
  }
}

static uint64_t fuzzer_utils_handle_open(int child_pid, uint32_t *drop_syscall, uint64_t file_name_guest_ptr, uint64_t mode)
{
  const char *file_name = (const char *) (uintptr_t) guest_to_host_addrress(file_name_guest_ptr);
#ifdef DROP_ICONV
  // Do not crash parent due to dynamically loading iconv plugins in the child
  if (strstr(file_name, "linux-gnu/gconv/gconv-modules")) {
    *drop_syscall = 1;
    return -ENOENT;
  }
#endif

  // Forcefully trigger crash when trying to write to the filesystem.
  // This most probably signifies some security issue.
  //
  // When it can be disabled via some setting, it most probably
  // should be disabled, otherwise it can clutter the entire system
  // like with the 'w' command in sed.
  if (child_pid && (mode & (O_WRONLY | O_RDWR | O_APPEND | O_CREAT)) != 0 && strcmp(file_name, "/dev/null")) {
    fprintf(stderr, "Opening %s for writing, exiting.\n", file_name);
    abort();
  }
  return 0;
}

/// Extended variant of watching for "dangerous" syscalls suggested on the AFL's mail list
static uint64_t catch_dangerous_syscalls(int child_pid, uint32_t num, uint32_t *drop_syscall, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
  switch (num) {
  case SYS_openat:
    return fuzzer_utils_handle_open(child_pid, drop_syscall, arg2, arg3);
  case SYS_open:
    return fuzzer_utils_handle_open(child_pid, drop_syscall, arg1, arg2);
  case SYS_execve:
    // Forcefully trigger crash in **parent** when invoking execve.
    // This is probably invoked from the forkserver's grand-child
    // after fork in a child process when spawning some process.
    // Disable this for the same reasons as the above.
    fprintf(stderr, "Trying to execve(%s, ...), exiting.\n", (const char *)guest_to_host_addrress(arg1));
    if (child_pid) { // supposing called from grand-child
      kill(child_pid, SIGABRT);
    }
    abort();
    break;
  }

  return 0;
}

#endif // FUZZER_UTILS_H
