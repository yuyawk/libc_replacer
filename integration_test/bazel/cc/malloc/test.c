#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static void *mock_malloc(size_t size) {
  // NOLINTNEXTLINE(performance-no-int-to-ptr)
  return (void *)size;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_malloc(mock_malloc);
  const size_t value_size = 123;
  const void *got = malloc(value_size);
  // NOLINTNEXTLINE(clang-analyzer-unix.Malloc,performance-no-int-to-ptr)
  assert(got == (void *)value_size);

  // Check the value after resetting
  libc_replacer_reset_malloc();
  const void *got_after_reset = malloc(value_size);
  // NOLINTNEXTLINE(clang-analyzer-unix.Malloc,performance-no-int-to-ptr)
  assert(got_after_reset != (void *)value_size);

  return 0;
}
