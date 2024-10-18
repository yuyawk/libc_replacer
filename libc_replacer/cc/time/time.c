#include "libc_replacer/cc/time/time.h" // IWYU pragma: associated
#include "libc_replacer/cc/internal/definition_helper.h"

#include <time.h>

LIBC_REPLACER_INTERNAL_DEFINE(time, time_t, (time_t *, tloc))
