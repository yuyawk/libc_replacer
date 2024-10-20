#include "libc_replacer/cc/timespec_get/timespec_get.h" // IWYU pragma: associated
#include "libc_replacer/cc/internal/definition_helper.h"

#include <time.h>

LIBC_REPLACER_INTERNAL_DEFINE(timespec_get, int, (struct timespec *, ts),
                              (int, base))
