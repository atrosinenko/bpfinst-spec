#ifndef BPFINST_COMMON_H
#define BPFINST_COMMON_H

#include <stdint.h>

/**
 * @brief Comparison operation condition
 *
 * Bitmask:
 * * 1 -- true if equal
 * * 2 -- true if left < right
 * * 4 -- true if left > right
 */
typedef enum {
  COND_NEVER = 0,  ///< 000 -- Never
  COND_EQ = 1,     ///< 001 -- a == b
  COND_LT = 2,     ///< 010 -- a < b
  COND_LE = 3,     ///< 011 -- a <= b
  COND_GT = 4,     ///< 100 -- a > b
  COND_GE = 5,     ///< 101 -- a >= b
  COND_NEQ = 6,    ///< 110 -- a != b
  COND_ALWAYS = 7, ///< 111 -- Always
} condition_op_t;

/// Result of comparison if operands are equal
#define COND_IF_EQ(x) (!!((x) & 1))
/// Result of comparison if first operand is less than the second one
#define COND_IF_LT(x) (!!((x) & 2))
/// Result of comparison if first operand is greater than the second one
#define COND_IF_GT(x) (!!((x) & 4))

#endif // BPFINST_COMMON_H
