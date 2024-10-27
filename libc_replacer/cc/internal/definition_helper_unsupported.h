#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_UNSUPPORTED_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_UNSUPPORTED_H_

#include <stdio.h>
#include <stdlib.h>

#if defined(__STDC_VERSION__) && 202311L <= __STDC_VERSION__
#define LIBC_REPLACER_INTERNAL_NORETURN [[noreturn]]
#else
#define LIBC_REPLACER_INTERNAL_NORETURN _Noreturn
#endif

/// @brief Define dummy replacer functions of an API.
/// @details This macro is used for defining the replacer of conditionally
/// enabled APIs.
/// Whether the target API is enabled or not, the build script sets the
/// linker option corresponding to the replacer.
/// This macro provides the dummy definitions of the target API to keep the
/// replacer compilable.
/// @param library Name of the libc API to replace.
#define LIBC_REPLACER_INTERNAL_DEFINE_UNSUPPORTED(library)                     \
  LIBC_REPLACER_INTERNAL_NORETURN void __wrap_##library(void) {                \
    fputs(stderr, "ERROR(libc_replacer): '" #library                           \
                  "' is not supported by the C compiler toolchain.\n");        \
    abort();                                                                   \
  }
#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_DEFINITION_HELPER_UNSUPPORTED_H_
