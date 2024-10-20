#include "libc_replacer/cc/clock/clock.h" // IWYU pragma: associated
#include "libc_replacer/cc/internal/definition_helper.h"

#include <time.h>

LIBC_REPLACER_INTERNAL_DEFINE(clock, clock_t, (void, ))
