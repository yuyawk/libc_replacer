#include "libc_replacer/cc/realloc/realloc.h"
#include "libc_replacer/cc/internal/definition_helper.h"

#include <stdlib.h>

LIBC_REPLACER_INTERNAL_DEFINE(realloc, void *, (void *, ptr), (size_t, size))
