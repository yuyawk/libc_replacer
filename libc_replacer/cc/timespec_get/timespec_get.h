#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_TIMESPEC_GET_TIMESPEC_GET_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_TIMESPEC_GET_TIMESPEC_GET_H_

#include "libc_replacer/cc/internal/declaration_helper.h"

#include <time.h>

LIBC_REPLACER_INTERNAL_DECLARE(timespec_get, int, (struct timespec *, ts_ptr),
                               (int, base))

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_TIMESPEC_GET_TIMESPEC_GET_H_
