#include <libc_replacer/cc/malloc.h>
#include <testing/testing.h>

#include <stdlib.h>

static const size_t size_init = 0;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t size_got = size_init;

static void *mock_malloc(size_t size) {
  TESTING_ASSERT_NE(size, size_init); // precondition
  size_got = size;
  return NULL;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_malloc(mock_malloc);
  const size_t value_size = 4;
  const void *const got = malloc(value_size);
  TESTING_ASSERT_EQ(got, NULL);
  TESTING_ASSERT_EQ(size_got, value_size);

  // Check the value after resetting
  libc_replacer_reset_malloc();
  size_got = size_init;
  void *const got_after_reset = malloc(value_size);
  TESTING_ASSERT_NE(got_after_reset, NULL);
  TESTING_ASSERT_EQ(size_got, size_init);

  free(got_after_reset);

  return 0;
}
