#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_CALLOC_CALLOC_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_CALLOC_CALLOC_H_

#include "libc_replacer/cc/internal/declaration_helper.h"

#include <stdlib.h>

LIBC_REPLACER_INTERNAL_DECLARE(calloc, void *, (size_t, nmemb), (size_t, size))

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_CALLOC_CALLOC_H_
