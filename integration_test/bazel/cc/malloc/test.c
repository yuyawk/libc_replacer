#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static const size_t size_init = 0;
static size_t size_got = size_init;

static void *mock_malloc(size_t size) {
  assert(size != size_init); // precondition
  size_got = size;
  return NULL;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_malloc(mock_malloc);
  const size_t value_size = 4;
  const void *got = malloc(value_size);
  assert(got == NULL);
  assert(size_got == value_size);

  // Check the value after resetting
  libc_replacer_reset_malloc();
  size_got = size_init;
  const void *got_after_reset = malloc(value_size);
  assert(got_after_reset != NULL);
  assert(size_got == size_init);

  free(got_after_reset);

  return 0;
}
