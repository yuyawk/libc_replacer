#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_REALLOC_REALLOC_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_REALLOC_REALLOC_H_

#include "libc_replacer/cc/internal/declaration_helper.h"

#include <stdlib.h>

LIBC_REPLACER_INTERNAL_DECLARE(realloc, void *, (void *, ptr), (size_t, size))

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_REALLOC_REALLOC_H_
