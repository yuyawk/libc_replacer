#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_H_

#include "libc_replacer/cc/internal/macro_impl.h"
#include <stdatomic.h>

/// @brief Define replacer functions of a libc API.
/// @param library Name of the libc API to replace.
/// @param ret_t Return value type of the libc API.
/// @param ... Argument value types of the libc API.
/// @note Disable `cppcoreguidelines-avoid-non-const-global-variables` for
/// defining a global atomic function pointer.
#define LIBC_REPLACER_INTERNAL_DEFINE(library, ret_t, ...)                                                                      \
  ret_t __real_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__));                                                             \
  ret_t __wrap_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__));                                                             \
  static _Atomic(libc_replacer_##library##_func_ptr_t) /* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */ \
      libc_replacer_##library##_global_func_ptr = __real_##library;                                                             \
  void libc_replacer_overwrite_##library(                                                                                       \
      libc_replacer_##library##_func_ptr_t func_new) {                                                                          \
    atomic_store(&libc_replacer_##library##_global_func_ptr, func_new);                                                         \
  }                                                                                                                             \
  void libc_replacer_reset_##library(void) {                                                                                    \
    atomic_store(&libc_replacer_##library##_global_func_ptr,                                                                    \
                 __real_##library);                                                                                             \
  }                                                                                                                             \
  ret_t __wrap_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__)) {                                                            \
    libc_replacer_##library##_func_ptr_t func_got =                                                                             \
        atomic_load(&libc_replacer_##library##_global_func_ptr);                                                                \
    LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(ret_t)                                                                            \
    func_got(LIBC_REPLACER_INTERNAL_GET_ARG_NAMES(__VA_ARGS__));                                                                \
  }

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_H_
