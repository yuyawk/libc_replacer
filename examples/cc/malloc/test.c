#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static void *mock_malloc(size_t size) { return (void *)size; }

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_malloc(mock_malloc);
  const void *got = malloc(123);
  assert(got == (void *)123);

  // Check the value after resetting
  libc_replacer_reset_malloc();
  const void *got_after_reset = malloc(123);
  assert(got_after_reset != (void *)123);

  return 0;
}
