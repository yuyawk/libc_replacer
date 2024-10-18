#ifndef INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_MACRO_IMPL_H_
#define INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_MACRO_IMPL_H_

/// @brief Extract the argument type from two elements expressing an argument.
/// @param type Type of the argument.
/// @param name Name of the argument.
#define LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS(type, name) type
/// @brief Extract the argument name from two elements expressing an argument.
/// @param type Type of the argument.
/// @param name Name of the argument.
#define LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS(type, name) name
/// @brief Extract the argument type the name from two elements expressing an argument.
/// @param type Type of the argument.
/// @param name Name of the argument.
#define LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS(type, name) type name

/// @brief Get the argument type from a two-element tuple expressing an argument.
/// @param type_name Two-element tuple of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE(type_name) LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS type_name
/// @brief Get the argument name from a two-element tuple expressing an argument.
/// @param type_name Two-element tuple of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE(type_name) LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS type_name
/// @brief Get the argument type and name from a two-element tuple expressing an argument.
/// @param type_name Two-element tuple of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE(type_name) LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS type_name

/// @brief Apply a function macro to one argument.
/// @param macro Function macro to apply.
/// @param target Target to apply the function macro.
#define LIBC_REPLACER_INTERNAL_APPLY_1(macro, target) macro(target)
/// @brief Apply a function macro to two arguments.
/// @param macro Function macro to apply.
/// @param target_1 Target to apply the function macro.
/// @param target_2 Target to apply the function macro.
#define LIBC_REPLACER_INTERNAL_APPLY_2(macro, target_1, target_2) LIBC_REPLACER_INTERNAL_APPLY_1(target_1), LIBC_REPLACER_INTERNAL_APPLY_1(target_2)
/// @brief Apply a function macro to three arguments.
/// @param macro Function macro to apply.
/// @param target_1 Target to apply the function macro.
/// @param target_2 Target to apply the function macro.
/// @param target_3 Target to apply the function macro.
#define LIBC_REPLACER_INTERNAL_APPLY_3(macro, target_1, target_2, target_3) LIBC_REPLACER_INTERNAL_APPLY_1(target_1), LIBC_REPLACER_INTERNAL_APPLY_2(target_2, target_3)
/// @brief Apply a function macro to four arguments.
/// @param macro Function macro to apply.
/// @param target_1 Target to apply the function macro.
/// @param target_2 Target to apply the function macro.
/// @param target_3 Target to apply the function macro.
/// @param target_4 Target to apply the function macro.
#define LIBC_REPLACER_INTERNAL_APPLY_4(macro, target_1, target_2, target_3, target_4) LIBC_REPLACER_INTERNAL_APPLY_1(target_1), LIBC_REPLACER_INTERNAL_APPLY_3(target_2, target_3, target_4)
/// @brief Apply a function macro to five arguments.
/// @param macro Function macro to apply.
/// @param target_1 Target to apply the function macro.
/// @param target_2 Target to apply the function macro.
/// @param target_3 Target to apply the function macro.
/// @param target_4 Target to apply the function macro.
/// @param target_5 Target to apply the function macro.
#define LIBC_REPLACER_INTERNAL_APPLY_5(macro, target_1, target_2, target_3, target_4, target_5) LIBC_REPLACER_INTERNAL_APPLY_1(target_1), LIBC_REPLACER_INTERNAL_APPLY_4(target_2, target_3, target_4, target_5)

/// @brief Implementation of @c LIBC_REPLACER_INTERNAL_COUNT.
#define LIBC_REPLACER_INTERNAL_COUNT_IMPL(_1, _2, _3, _4, _5, number, ...) number
/// @brief Count number of arguments in a variadic expression.
#define LIBC_REPLACER_INTERNAL_COUNT(...) LIBC_REPLACER_INTERNAL_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0)

/// @brief Implementation of @c LIBC_REPLACER_INTERNAL_APPLY.
/// @param macro Function macro to apply.
/// @param number Number of targets.
#define LIBC_REPLACER_INTERNAL_APPLY_IMPL_EXPAND(macro, number, ...) LIBC_REPLACER_INTERNAL_APPLY_##number(macro, __VA_ARGS__)
/// @brief Implementation of @c LIBC_REPLACER_INTERNAL_APPLY.
/// @param macro Function macro to apply.
/// @param number Number of targets.
#define LIBC_REPLACER_INTERNAL_APPLY_IMPL(macro, number, ...) LIBC_REPLACER_INTERNAL_APPLY_IMPL_EXPAND(macro, number, __VA_ARGS__)
/// @brief Apply function arguments to targets.
/// @param macro Function macro to apply.
#define LIBC_REPLACER_INTERNAL_APPLY(macro, ...) LIBC_REPLACER_INTERNAL_APPLY_IMPL(macro, LIBC_REPLACER_INTERNAL_COUNT(__VA_ARGS__), __VA_ARGS__)

/// @brief Get the argument types from a variadic list of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_TYPES(...) LIBC_REPLACER_INTERNAL_APPLY(LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE, __VA_ARGS__)
/// @brief Get the argument names from a variadic list of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_NAMES(...) LIBC_REPLACER_INTERNAL_APPLY(LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE, __VA_ARGS__)
/// @brief Get the argument types and names from a variadic list of "(type, name)".
#define LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(...) LIBC_REPLACER_INTERNAL_APPLY(LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE, __VA_ARGS__)

/// @brief Dummy type declaration.
/// @details Declared because ISO C requires a translation unit to contain at least one declaration.
/// Once there appears a non-dummy declaration, it can be removed.
typedef int libc_replacer_internal_dummy_typedef;

#endif // INCLUDE_GUARD_LIBC_REPLACER_CC_INTERNAL_MACRO_IMPL_H_