#include "libc_replacer/cc/malloc/malloc.h"
#include "libc_replacer/cc/internal/definition_helper.h"

#include <stdlib.h>

LIBC_REPLACER_INTERNAL_DEFINE(malloc, void *, (size_t, size))
