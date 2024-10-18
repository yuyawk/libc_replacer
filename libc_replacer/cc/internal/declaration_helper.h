#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DECLARATION_HELPER_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DECLARATION_HELPER_H_

#include "libc_replacer/cc/internal/macro_impl.h"

#ifdef __cplusplus
/// @brief Marker for the start of declaration in a header.
#define LIBC_REPLACER_INTERNAL_DECLARATION_START extern "C" {
/// @brief Marker for the end of declaration in a header.
#define LIBC_REPLACER_INTERNAL_DECLARATION_END }
#else
#define LIBC_REPLACER_INTERNAL_DECLARATION_START
#define LIBC_REPLACER_INTERNAL_DECLARATION_END
#endif // __cplusplus

/// @brief Declare replacer functions of a libc API.
/// @param library Name of the libc API to replace.
/// @param ret_t Return value type of the libc API.
/// @param ... Argument value types of the libc API.
#define LIBC_REPLACER_INTERNAL_DECLARE(library, ret_t, ...)                    \
  LIBC_REPLACER_INTERNAL_DECLARATION_START                                     \
  typedef ret_t (*libc_replacer_##library##_func_ptr_t)(                       \
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(__VA_ARGS__));            \
  void libc_replacer_overwrite_##library(                                      \
      libc_replacer_##library##_func_ptr_t func_new);                          \
  void libc_replacer_reset_##library(void);                                    \
  LIBC_REPLACER_INTERNAL_DECLARATION_END

/// @brief Dummy type declaration.
/// @details Declared because ISO C requires a translation unit to contain at
/// least one declaration. Once there appears a non-dummy declaration, it can be
/// removed.
typedef int libc_replacer_declaration_helper_dummy_typedef;

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DECLARATION_HELPER_H_
