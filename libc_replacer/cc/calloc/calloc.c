#include "libc_replacer/cc/calloc/calloc.h"
#include "libc_replacer/cc/internal/definition_helper.h"

#include <stdlib.h>

LIBC_REPLACER_INTERNAL_DEFINE(calloc, void *, (size_t, nmemb), (size_t, size))
