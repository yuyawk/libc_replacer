#ifndef LIBC_REPLACER_CC_TIME_TIME_H_
#define LIBC_REPLACER_CC_TIME_TIME_H_

#include <time.h>

/// @brief Type of the function pointer to @c time().
typedef time_t (*time_func_ptr_t)(time_t *tloc);

/// @brief Overwrite @c time().
/// @param func_new Function pointer to overwrite.
/// @post @c time() is overwritten by @c func_new
void libc_replacer_overwrite_time(time_func_ptr_t func_new);

/// @brief Reset @c time().
/// @post @c time() is reset to the original API.
void libc_replacer_reset_time();

#endif // LIBC_REPLACER_CC_TIME_TIME_H_
