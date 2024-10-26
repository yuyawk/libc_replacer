#include <libc_replacer/cc/interface.h>
#include <testing/testing.h>

#include <stdbool.h>
#include <stdlib.h>

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static bool is_called = false;

static void mock_free(void *ptr) {
  (void)ptr;
  is_called = true;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_free(mock_free);
  // Note: Avoid providing a `NULL` constant to prevent the compiler
  // from optimizing away `free(NULL)`
  void *const volatile null_ptr = NULL;
  free(null_ptr);
  TESTING_ASSERT_TRUE(is_called);
  TESTING_ASSERT_EQ(null_ptr, NULL);

  // Check the value after resetting
  libc_replacer_reset_free();
  is_called = false;
  free(null_ptr);
  TESTING_ASSERT_FALSE(is_called);

  return 0;
}
