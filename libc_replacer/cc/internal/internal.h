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

/// @brief Dummy type declaration.
/// @details Declared because ISO C requires a translation unit to contain at least one declaration.
/// Once there appears a non-dummy declaration, it can be removed.
typedef int libc_replacer_internal_dummy_typedef;

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_INTERNAL_H_
