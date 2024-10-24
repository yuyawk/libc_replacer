#include "libc_replacer/cc/free/free.h" // IWYU pragma: associated
#include "libc_replacer/cc/internal/definition_helper.h"

LIBC_REPLACER_INTERNAL_DEFINE_RETURNING_VOID(free, (void *, ptr))
