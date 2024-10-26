#include "libc_replacer/cc/internal/macro_impl.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Test utility functions
#define TEST_ASSERT_TOKEN_EQ_IMPL(lhs, rhs, expected_equal)                    \
  do {                                                                         \
    if ((strcmp(#lhs, #rhs) == 0) != expected_equal) {                         \
      if (expected_equal) {                                                    \
        fprintf(stderr, "TEST_ASSERT_TOKEN_EQ failed: '" #lhs " == " #rhs      \
                        "' is not satisfied.\n");                              \
      } else {                                                                 \
        fprintf(stderr, "TEST_ASSERT_TOKEN_NE failed: '" #lhs " != " #rhs      \
                        "' is not satisfied.\n");                              \
      }                                                                        \
      assert(0);                                                               \
    }                                                                          \
  } while (0)
#define TEST_ASSERT_TOKEN_EQ(lhs, rhs) TEST_ASSERT_TOKEN_EQ_IMPL(lhs, rhs, 1)
#define TEST_ASSERT_TOKEN_NE(lhs, rhs) TEST_ASSERT_TOKEN_EQ_IMPL(lhs, rhs, 0)

// For testing `LIBC_REPLACER_INTERNAL_APPLY`
#define ADD_FOO(arg) FOO##arg

int main(void) {
  // Test LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS(int, param), int);

  // Test LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS(int, param), param);

  // Test LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS(int, param),
      int param);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE((int, param)), int);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE((int, param)), param);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE((int, param)),
      int param);

  // Test LIBC_REPLACER_INTERNAL_COUNT
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one), 1);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two), 2);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two, three), 3);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two, three, four), 4);
  TEST_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_COUNT(one, two, three, four, five), 5);

  // Test LIBC_REPLACER_INTERNAL_APPLY
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one), FOOone);
  TEST_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two)),
                       (FOOone, FOOtwo));
  TEST_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three)),
                       (FOOone, FOOtwo, FOOthree));
  TEST_ASSERT_TOKEN_EQ(
      (LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three, four)),
      (FOOone, FOOtwo, FOOthree, FOOfour));
  TEST_ASSERT_TOKEN_EQ(
      (LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three, four, five)),
      (FOOone, FOOtwo, FOOthree, FOOfour, FOOfive));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPES
  TEST_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_TYPES(
                           (int, foo), (void, ), (float, bar))),
                       (int, void, float));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_NAMES
  TEST_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_NAMES(
                           (int, foo), (void, ), (float, bar))),
                       (foo, , bar));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES
  // clang-format off
  TEST_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(
                           (int, foo), (void, ), (float, bar))),
                       (int foo, void , float bar));
  // clang-format on

  // Test LIBC_REPLACER_INTERNAL_CONCATENATE
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_CONCATENATE(foo, bar), foobar);

  // Test LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(int), return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(float),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(double),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(time_t),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void), );
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void_t),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void *),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void **),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void ***),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void ****),
                       return);
  TEST_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void *****),
                       return);

  return 0;
}
