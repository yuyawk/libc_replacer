#include "libc_replacer/cc/internal/macro_impl.h"

#include <testing/testing.h>

#include <stdio.h>
#include <string.h>

// For testing `LIBC_REPLACER_INTERNAL_APPLY`
#define ADD_FOO(arg) FOO##arg

int main(void) {
  // Test LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_TYPE_FROM_TWO_ELEMENTS(int, param), int);

  // Test LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_NAME_FROM_TWO_ELEMENTS(int, param), param);

  // Test LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_TYPE_AND_NAME_FROM_TWO_ELEMENTS(int, param),
      int param);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_FROM_TUPLE((int, param)), int);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_NAME_FROM_TUPLE((int, param)), param);

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_GET_ARG_TYPE_AND_NAME_FROM_TUPLE((int, param)),
      int param);

  // Test LIBC_REPLACER_INTERNAL_COUNT
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one), 1);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two), 2);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two, three), 3);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_COUNT(one, two, three, four),
                          4);
  TESTING_ASSERT_TOKEN_EQ(
      LIBC_REPLACER_INTERNAL_COUNT(one, two, three, four, five), 5);

  // Test LIBC_REPLACER_INTERNAL_APPLY
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one), FOOone);
  TESTING_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two)),
                          (FOOone, FOOtwo));
  TESTING_ASSERT_TOKEN_EQ(
      (LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three)),
      (FOOone, FOOtwo, FOOthree));
  TESTING_ASSERT_TOKEN_EQ(
      (LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three, four)),
      (FOOone, FOOtwo, FOOthree, FOOfour));
  TESTING_ASSERT_TOKEN_EQ(
      (LIBC_REPLACER_INTERNAL_APPLY(ADD_FOO, one, two, three, four, five)),
      (FOOone, FOOtwo, FOOthree, FOOfour, FOOfive));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPES
  TESTING_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_TYPES(
                              (int, foo), (void, ), (float, bar))),
                          (int, void, float));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_NAMES
  TESTING_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_NAMES(
                              (int, foo), (void, ), (float, bar))),
                          (foo, , bar));

  // Test LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES
  // clang-format off
  TESTING_ASSERT_TOKEN_EQ((LIBC_REPLACER_INTERNAL_GET_ARG_TYPES_AND_NAMES(
                           (int, foo), (void, ), (float, bar))),
                       (int foo, void , float bar));
  // clang-format on

  // Test LIBC_REPLACER_INTERNAL_CONCATENATE
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_CONCATENATE(foo, bar), foobar);

  // Test LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(int),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(float),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(double),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(time_t),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void), );
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void_t),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void *),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void **),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void ***),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void ****),
                          return);
  TESTING_ASSERT_TOKEN_EQ(LIBC_REPLACER_INTERNAL_RETURN_IF_NOT_VOID(void *****),
                          return);

  return 0;
}
