#include "libc_replacer/cc/clock_gettime/clock_gettime.h" // IWYU pragma: associated
#include "libc_replacer/cc/clock_gettime/features.h"

#ifdef LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME
#include "libc_replacer/cc/internal/definition_helper_syscall.h"
#include <time.h>

LIBC_REPLACER_INTERNAL_DEFINE_SYSCALL(clock_gettime, int, (clockid_t, clk_id),
                                      (struct timespec *, ts_ptr))
#else

/// @brief Dummy type declaration.
/// @details Declared because ISO C requires a translation unit to contain at
/// least one declaration.
typedef int libc_replacer_internal_dummy_typedef_clock_gettime;

#endif // LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME
