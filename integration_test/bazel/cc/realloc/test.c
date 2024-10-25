#include <libc_replacer/cc/interface.h>

#include <assert.h>
#include <stdlib.h>

static const size_t size_init = 0;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static size_t size_got = size_init;

static void *mock_realloc(void *ptr, size_t size) {
  (void)ptr;
  assert(size != size_init); // precondition
  size_got = size;
  return NULL;
}

int main(void) {
  // Check if the API is replaced
  libc_replacer_overwrite_realloc(mock_realloc);
  const size_t size = 6;
  // Note: Avoid providing a NULL constant to prevent compiler
  // from optimizing realloc(NULL, size) to malloc(size)
  void *ptr = NULL;
  const void *got = realloc(ptr, size);
  assert(got == NULL);
  assert(size_got == size);

  // Check the value after resetting
  size_got = size_init;
  libc_replacer_reset_realloc();
  void *got_after_reset = realloc(NULL, size);
  assert(got_after_reset != NULL);
  assert(size_got == size_init);

  free(got_after_reset);

  return 0;
}
