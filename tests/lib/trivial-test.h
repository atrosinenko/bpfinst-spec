#ifndef TRIVIAL_TEST_H
#define TRIVIAL_TEST_H

/**
 * Expected usage:
 *
 * // test-program.c:
 * #define PROGRAM
 * #include "../lib/trivial-test.h"
 * TEST_FOR_TYPE(int, "%d")
 *
 * // inst-bpf.h:
 * #define EBPF
 * #include "../lib/trivial-test.h"
 *
 * BEGIN_EBPF_HANDLER
 *   BEGIN_INPUTS
 *   EXPECT_INPUT(100, 11)
 *   END_INPUTS
 *
 *   slow_call(arg1 - arg2);
 *
 * END_EBPF_HANDLER
 */

#if !defined(PROGRAM) && !defined(EBPF)
#   error Either PROGRAM or EBPF macro should be declared
#elif defined(PROGRAM) && defined(EBPF)
#   error Only one of PROGRAM and EBPF macro should be declared
#endif

#ifdef PROGRAM
#   include <stdio.h>
#   include <stdint.h>
#else
#   include <bpfinst/bpf.h>
#endif

#define BEGIN_EBPF_HANDLER void inst_sub(uint64_t arg1, uint64_t arg2) {
#define END_EBPF_HANDLER }

// These are macro to match constant values with high probability
// while trying to hinder compiler optimizations based on this equality.
// Trying to restrict to quite trivial operations (not div, rem, etc.) to
// not introduce new non-trivial tested assumptions (that can clutter test results).

#define MATCH_PAIR(x, y, a, b) (((((x) ^ (a)) & 65535) == 0) && ((((y) ^ (b)) & 65535) == 0))

#define BEGIN_INPUTS int input_matched = 0;
#define EXPECT_INPUT(a, b) if (MATCH_PAIR(arg1, arg2, a, b)) input_matched = 1;
#define END_INPUTS if (!input_matched) return;

#define TEST_FOR_TYPE(tpe, fmt) \
  volatile tpe x, y, z; \
  int main(int argc, const char *argv[]) \
  { \
    scanf(fmt " " fmt, &x, &y); \
    z = x - y; \
    return 0; \
  }

#endif // TRIVIAL_TEST_H
