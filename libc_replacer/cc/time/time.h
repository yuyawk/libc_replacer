#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_

#include "libc_replacer/cc/internal/internal.h"

#include <time.h>

LIBC_REPLACER_DECLARATION_START

/// @brief Type of the function pointer to @c time().
typedef time_t (*libc_replacer_time_func_ptr_t)(time_t *tloc);

/// @brief Overwrite @c time().
/// @param func_new Function pointer to overwrite.
/// @post @c time() is overwritten by @c func_new
void libc_replacer_overwrite_time(libc_replacer_time_func_ptr_t func_new);

/// @brief Reset @c time().
/// @post @c time() is reset to the original API.
void libc_replacer_reset_time(void);

LIBC_REPLACER_DECLARATION_END

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_
