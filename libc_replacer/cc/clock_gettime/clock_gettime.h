#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_CLOCK_GETTIME_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_CLOCK_GETTIME_H_

#include "libc_replacer/cc/clock_gettime/features.h"

#ifdef LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME
#include "libc_replacer/cc/internal/declaration_helper.h"
#include <time.h>

LIBC_REPLACER_INTERNAL_DECLARE(clock_gettime, int, (clockid_t, clk_id),
                               (struct timespec *, ts_ptr))

#endif // LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_CLOCK_GETTIME_H_
