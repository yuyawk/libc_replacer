#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_FEATURES_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_FEATURES_H_

#if defined(__unix__) ||                                                       \
    (defined(__APPLE__) &&                                                     \
     defined(__MACH__)) // Check if the platform is unix-compliant
#include <unistd.h>
#ifdef _POSIX_VERSION // Check if the platform is POSIX-compliant

#define LIBC_REPLACER_INTERNAL_HAS_CLOCK_GETTIME

// IWYU pragma: begin_exports
#include <sys/types.h>
typedef clockid_t clockid_t;
// IWYU pragma: end_exports

#endif // _POSIX_VERSION
#endif // defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_CLOCK_GETTIME_FEATURES_H_
