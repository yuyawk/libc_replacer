#ifndef INCLUDE_GUARD_LIBC_REPLACER_INTERNAL_DEVELOPMENT_TESTING_TESTING_H_
#define INCLUDE_GUARD_LIBC_REPLACER_INTERNAL_DEVELOPMENT_TESTING_TESTING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Abort if @c expr is not @c true.
/// @param expr Expression to test.
#define TESTING_ASSERT_TRUE(expr)                                                                                \
  do {                                                                                                           \
    if (!(expr)) {                                                                                               \
      int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
          fprintf(                                                                                               \
              stderr,                                                                                            \
              "(TESTING_ASSERT_TRUE) Assertion failed: %s is false, function "                                   \
              "%s, file %s, line %d.\n",                                                                         \
              #expr, __func__, __FILE__, __LINE__);                                                              \
      (void)discarded;                                                                                           \
      abort();                                                                                                   \
    }                                                                                                            \
  } while (0)

/// @brief Abort if @c expr is not @c false.
/// @param expr Expression to test.
#define TESTING_ASSERT_FALSE(expr)                                                                               \
  do {                                                                                                           \
    if ((expr)) {                                                                                                \
      int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
          fprintf(                                                                                               \
              stderr,                                                                                            \
              "(TESTING_ASSERT_FALSE) Assertion failed: %s is true, function "                                   \
              "%s, file %s, line %d.\n",                                                                         \
              #expr, __func__, __FILE__, __LINE__);                                                              \
      (void)discarded;                                                                                           \
      abort();                                                                                                   \
    }                                                                                                            \
  } while (0)

/// @brief Abort if @c lhs is not evaluated to the equal run-time value to
/// @c rhs.
/// @param lhs Left-hand side.
/// @param rhs Right-hand side.
#define TESTING_ASSERT_EQ(lhs, rhs)                                                                              \
  do {                                                                                                           \
    if ((lhs) != (rhs)) {                                                                                        \
      int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
          fprintf(                                                                                               \
              stderr,                                                                                            \
              "(TESTING_ASSERT_EQ) Assertion failed: %s == %s, function %s, "                                    \
              "file %s, line %d.\n",                                                                             \
              #lhs, #rhs, __func__, __FILE__, __LINE__);                                                         \
      (void)discarded;                                                                                           \
      abort();                                                                                                   \
    }                                                                                                            \
  } while (0)

/// @brief Abort if @c lhs is evaluated to the equal run-time value to  @c rhs.
/// @param lhs Left-hand side.
/// @param rhs Right-hand side.
#define TESTING_ASSERT_NE(lhs, rhs)                                                                              \
  do {                                                                                                           \
    if ((lhs) == (rhs)) {                                                                                        \
      int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
          fprintf(                                                                                               \
              stderr,                                                                                            \
              "(TESTING_ASSERT_NE) Assertion failed: %s != %s, function %s, "                                    \
              "file %s, line %d.\n",                                                                             \
              #lhs, #rhs, __func__, __FILE__, __LINE__);                                                         \
      (void)discarded;                                                                                           \
      abort();                                                                                                   \
    }                                                                                                            \
  } while (0)

/// @brief Implementation of @c TESTING_ASSERT_TOKEN_EQ and
/// @c TESTING_ASSERT_TOKEN_NE.
/// @param lhs Left-hand side.
/// @param rhs Right-hand side.
/// @param expected_equal 1 if the two are expected to equal, 0 otherwise
#define TESTING_ASSERT_TOKEN_EQ_IMPLEMENTATION(lhs, rhs, expected_equal)                                           \
  do {                                                                                                             \
    if ((strcmp(#lhs, #rhs) == 0) != (expected_equal)) {                                                           \
      if (expected_equal) {                                                                                        \
        int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
            fprintf(stderr,                                                                                        \
                    "(TESTING_ASSERT_TOKEN_EQ) Assertion failed: %s "                                              \
                    "== %s, function %s, file %s, line %d.\n",                                                     \
                    #lhs, #rhs, __func__, __FILE__, __LINE__);                                                     \
        (void)discarded;                                                                                           \
      } else {                                                                                                     \
        int discarded = /* NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) */ \
            fprintf(stderr,                                                                                        \
                    "(TESTING_ASSERT_TOKEN_NE) Assertion failed: %s "                                              \
                    "!= %s, function %s, file %s, line %d.\n",                                                     \
                    #lhs, #rhs, __func__, __FILE__, __LINE__);                                                     \
        (void)discarded;                                                                                           \
      }                                                                                                            \
      abort();                                                                                                     \
    }                                                                                                              \
  } while (0)

/// @brief Abort if @c lhs is not an equal compile-time token to @c rhs.
/// @param lhs Left-hand side.
/// @param rhs Right-hand side.
#define TESTING_ASSERT_TOKEN_EQ(lhs, rhs)                                      \
  TESTING_ASSERT_TOKEN_EQ_IMPLEMENTATION(lhs, rhs, 1)

/// @brief Abort if @c lhs is an equal compile-time token to @c rhs.
/// @param lhs Left-hand side.
/// @param rhs Right-hand side.
#define TESTING_ASSERT_TOKEN_NE(lhs, rhs)                                      \
  TESTING_ASSERT_TOKEN_EQ_IMPLEMENTATION(lhs, rhs, 0)

#endif // INCLUDE_GUARD_LIBC_REPLACER_INTERNAL_DEVELOPMENT_TESTING_TESTING_H_
