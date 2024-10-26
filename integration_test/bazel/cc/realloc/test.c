#include <libc_replacer/cc/interface.h>
#include <testing/testing.h>

#include <stdlib.h>

static const size_t size_init = 0;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t size_got = size_init;

static void *mock_realloc(void *ptr, size_t size) {
  TESTING_ASSERT_NE(size, size_init); // precondition
  size_got = size;
  return ptr;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_realloc(mock_realloc);
  const size_t size = 6;
  // Note: Avoid providing a `NULL` constant to prevent the compiler
  // from optimizing `realloc(NULL, size)` to `malloc(size)`
  void *const volatile null_ptr = NULL;
  const void *const got = realloc(null_ptr, size);
  TESTING_ASSERT_EQ(got, NULL);
  TESTING_ASSERT_EQ(size_got, size);

  // Check the value after resetting
  size_got = size_init;
  libc_replacer_reset_realloc();
  void *const got_after_reset = realloc(null_ptr, size);
  TESTING_ASSERT_NE(got_after_reset, NULL);
  TESTING_ASSERT_EQ(size_got, size_init);

  free(got_after_reset);

  return 0;
}
