/**
 * @file
 *
 * @brief API of the eBPF-side of the instrumenter
 *
 * This header is expected to be included into source files
 * to be compiled as eBPF object code.
 */

#ifndef BPFINST_BPF_H
#define BPFINST_BPF_H

#include <bpfinst/common.h>

/// \defgroup engine-bpf Functions to be provided by the instrumentation engine to eBPF code
/// @{

/**
 * @brief Performs call to native instrumenter via event_dispatch_slow_call().
 *
 * @returns Value returned by the native code
 */
uint64_t slow_call(uint64_t funct);

/**
 * @brief Get some pseudo program counter value to be used for hashing
 *
 * @note The **real** PC value can be unknown at the time of instrumentation.
 */
uint64_t pseudo_pc(void);

/**
 * @brief Get the condition of the branch or comparison being currently instrumented
 *
 * @warning Behavior is undefined if currently instrumented instruction
 *          is nor branch nor comparison!
 */
condition_op_t condition(void);

/**
 * @brief Get the computed result of the branch or comparison being currently instrumented
 *
 * @warning Behavior is undefined if curretly instrumented instruction
 *          is nor branch nor comparison!
 */
uint64_t condition_result(void);

void stop_if_no_tags(void);

/**
 * @brief Set tag for the result of the instruction being instrumented
 */
void set_tag(uint64_t tag);

/**
 * @brief Get width in bits of the result of instruction being instrumented
 */
uint64_t bit_width_res(void);

/**
 * @brief Get width in bits of the first operand of instruction being instrumented
 */
uint64_t bit_width1(void);

/**
 * @brief Get width in bits of the second operand of instruction being instrumented
 */
uint64_t bit_width2(void);

/**
 * @brief Get width in bits of the third operand of instruction being instrumented
 */
uint64_t bit_width3(void);

/**
 * @brief Get the tag associated with the first operand
 */
uint64_t tag1(void);

/**
 * @brief Get the tag associated with the second operand
 */
uint64_t tag2(void);

/**
 * @brief Get the tag associated with the third operand
 */
uint64_t tag3(void);


/// @}

/// \defgroup instrumenter-bpf Functions to be implemented by the instrumenter, if required (in eBPF object)
/// @{

// Arithmetic:

/**
 * @brief Instrumenter for x = a + b
 */
void inst_add(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a - b
 */
void inst_sub(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = -a
 */
void inst_neg(uint64_t a);

/**
 * @brief Instrumenter for x = a * b (all of the same width)
 */
void inst_mul(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a / b (unsigned)
 */
void inst_udiv(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a / b (signed)
 */
void inst_sdiv(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a % b (unsigned)
 */
void inst_urem(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a % b (signed)
 *
 * @note This instrumenter is used if and only if the instrumented operation
 *       is required to always return non-negative result.
 */
void inst_srem_nonneg(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a % b (signed)
 *
 * @note This instrumenter is used if and only if the instrumented operation
 *       is required to always return the result of the same sign as its
 *       first operand.
 */
void inst_srem_1starg(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a % b (signed)
 *
 * @note This instrumenter is used if and only if the instrumented operation
 *       is required to always return the result of the same sign as its
 *       second operand.
 */
void inst_srem_2ndarg(uint64_t a, uint64_t b);

// Logical:

/**
 * @brief Instrumenter for x = a & b (bit-wise)
 */
void inst_and(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = ~(a & b) (bit-wise)
 */
void inst_nand(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a | b (bit-wise)
 */
void inst_or(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = ~(a | b) (bit-wise)
 */
void inst_nor(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = a ^ b (bit-wise)
 */
void inst_xor(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = ~(a ^ b) (bit-wise)
 */
void inst_eqv(uint64_t a, uint64_t b);

/**
 * @brief Instrumenter for x = ~a (bit-wise)
 */
void inst_not(uint64_t a);

/**
 * @brief Instrumenter for x = (a != 0) ? clz(a) : if0
 */
void inst_clz(uint64_t a, uint64_t if0);

/**
 * @brief Instrumenter for x = (a != 0) ? ctz(a) : if0
 */
void inst_ctz(uint64_t a, uint64_t if0);

/**
 * @brief Instrumenter for x = a << sh
 */
void inst_shl(uint64_t a, uint64_t sh);

/**
 * @brief Instrumenter for x = a >> sh (unsigned aka logical)
 */
void inst_lshr(uint64_t a, uint64_t sh);

/**
 * @brief Instrumenter for x = a >> sh (signed aka arithmetic)
 */
void inst_ashr(uint64_t a, uint64_t sh);

void inst_cmp(uint64_t a, uint64_t b);

// Misc:

void inst_br(uint64_t cond);

void inst_indirectbr(void);

void inst_trunc(uint64_t a);

void inst_zext(uint64_t a);

void inst_sext(uint64_t a);

/**
 * @brief Instrumenter for x = *(addr + offset)
 *
 * @see bit_width()
 */
void inst_load(uint64_t addr, int64_t offset);

/**
 * @brief Instrumenter for *(addr + offset) = value
 *
 * @see bit_width()
 */
void inst_store(uint64_t addr, int64_t offset, uint64_t value);

/// @}

#endif // BPFINST_BPF_H
