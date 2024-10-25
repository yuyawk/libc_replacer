#include <libc_replacer/cc/interface.h>

#include <assert.h>
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
  free(NULL);
  assert(is_called);

  // Check the value after resetting
  libc_replacer_reset_free();
  is_called = false;
  free(NULL);
  assert(!is_called);

  return 0;
}
