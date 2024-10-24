#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static void *mock_realloc(void *ptr, size_t size) {
  *(size_t *)ptr = size;
  return ptr;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_realloc(mock_realloc);
  const size_t size = 10;
  size_t value = 0;
  const void *got = realloc(&value, size);
  assert(got == &value);
  assert(value == size);

  libc_replacer_reset_realloc();

  return 0;
}
