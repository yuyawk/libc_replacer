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
#define LIBC_REPLACER_INTERNAL_DEFINE(library, ret_t, ...)                     \
  LIBC_REPLACER_INTERNAL_DEFINE_IMPLEMENTATION(library, ret_t, return,         \
                                               __VA_ARGS__)

/// @brief @c LIBC_REPLACER_INTERNAL_DEFINE for the case where @c ret_t is @c
/// void.
/// @details In C, @c return keyword shall not be used for
/// @param library Name of the libc API to replace.
/// @param ... Argument value types of the libc API.
/// @note Disable `cppcoreguidelines-avoid-non-const-global-variables` for
/// defining a global atomic function pointer.
#define LIBC_REPLACER_INTERNAL_DEFINE_RETURNING_VOID(library, ...)             \
  LIBC_REPLACER_INTERNAL_DEFINE_IMPLEMENTATION(library, void, , __VA_ARGS__)

/// @brief Implementation of @c LIBC_REPLACER_INTERNAL_DEFINE and @c
/// LIBC_REPLACER_INTERNAL_DEFINE_RETURNING_VOID
/// @param library Name of the libc API to replace.
/// @param ret_t Return value type of the libc API.
/// @param return_kw @c return if @c ret_t is non-void, empty otherwise
/// @param ... Argument value types of the libc API.
/// @note Disable `cppcoreguidelines-avoid-non-const-global-variables` for
/// defining a global atomic function pointer.
#define LIBC_REPLACER_INTERNAL_DEFINE_IMPLEMENTATION(library, ret_t,                                                            \
                                                     return_kw, ...)                                                            \
  ret_t __real_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__));                                                             \
  ret_t __wrap_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__));                                                             \
  static _Atomic(libc_replacer_##library##_func_ptr_t) /* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */ \
      libc_replacer_func_global = __real_##library;                                                                             \
  void libc_replacer_overwrite_##library(                                                                                       \
      libc_replacer_##library##_func_ptr_t func_new) {                                                                          \
    atomic_store(&libc_replacer_func_global, func_new);                                                                         \
  }                                                                                                                             \
  void libc_replacer_reset_##library(void) {                                                                                    \
    atomic_store(&libc_replacer_func_global, __real_##library);                                                                 \
  }                                                                                                                             \
  ret_t __wrap_##library(                                                                                                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__)) {                                                            \
    libc_replacer_##library##_func_ptr_t func_got =                                                                             \
        atomic_load(&libc_replacer_func_global);                                                                                \
    return_kw func_got(LIBC_REPLACER_INTERNAL_GET_ARG_NAMES(__VA_ARGS__));                                                      \
  }

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_H_
