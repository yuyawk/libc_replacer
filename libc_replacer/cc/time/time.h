#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_

#include "libc_replacer/cc/internal/declaration_helper.h"

#include <time.h>

LIBC_REPLACER_INTERNAL_DECLARE(time, time_t, (time_t *, tloc))

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_TIME_TIME_H_
