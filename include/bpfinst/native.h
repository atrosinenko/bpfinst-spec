/**
 * @file
 *
 * @brief API of the native side of the instrumenter.
 *
 * This file is expected to be included into source files
 * to be compiled as a native library.
 */

#ifndef BPFINST_NATIVE_H
#define BPFINST_NATIVE_H

#include <bpfinst/common.h>

/// \defgroup engine-native Functions to be provided by the instrumentation engine to native code
/// @{

/**
 * @brief Translates host address (as seen by instrumenter) to guest virtual address.
 */
uint64_t host_to_virtual_addrress(uint64_t address);

/**
 * @brief Translates host address (as seen by instrumenter) to guest physical address.
 *
 * @note If used for user-space instrumentation, the same as host_to_virtual_addrress().
 */
uint64_t host_to_physical_addrress(uint64_t address);

/// @}

/// \defgroup instrumenter-native Functions to be implemented by the instrumenter, if required (in native library)
/// @{

/**
 * @brief Callback to be called via slow_call() from the eBPF instrumenter part.
 *
 * If you need more arguments, use global variables.
 */
uint64_t event_dispatch_slow_call(uint64_t funct);

/**
 * @brief Callback to be called before instrumented application performs system call.
 *
 * @param num          Host system call number
 * @param drop_syscall If set to non-zero, the system call will not be executed
 * @param arg1         The first syscall argument
 * @param arg2         The second syscall argument
 * @param arg3         The third syscall argument
 * @param arg4         The fourth syscall argument
 * @param arg5         The fifth syscall argument
 * @param arg6         The sixth syscall argument
 * @return The returned value will be returned as system call result if requested
 *         to drop this syscall, otherwise ignored.
 */
uint64_t event_before_syscall(uint32_t num, uint32_t *drop_syscall,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5, uint64_t arg6);

/// @}

#endif // BPFINST_NATIVE_H
