#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_INTERNAL_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_INTERNAL_H_

#ifdef __cplusplus
/// @brief Marker for the start of declaration in a header.
#define LIBC_REPLACER_DECLARATION_START \
    extern "C"                          \
    {
/// @brief Marker for the end of declaration in a header.
#define LIBC_REPLACER_DECLARATION_END }
#else
#define LIBC_REPLACER_DECLARATION_START
#define LIBC_REPLACER_DECLARATION_END
#endif // __cplusplus

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_INTERNAL_H_
