#include "libc_replacer/cc/clock_gettime/clock_gettime.h" // IWYU pragma: associated
#include "libc_replacer/cc/clock_gettime/features.h"
#include "libc_replacer/cc/internal/definition_helper_syscall.h"
#include "libc_replacer/cc/internal/definition_helper_unsupported.h"
#include <time.h>

#ifdef LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME

LIBC_REPLACER_INTERNAL_DEFINE_SYSCALL(clock_gettime, int, (clockid_t, clk_id),
                                      (struct timespec *, ts_ptr))

#else

LIBC_REPLACER_INTERNAL_DEFINE_UNSUPPORTED(clock_gettime)
LIBC_REPLACER_INTERNAL_DEFINE_UNSUPPORTED(__clock_gettime)

#endif // LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME
